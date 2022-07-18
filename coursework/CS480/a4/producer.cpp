
#include "producer.hpp"
#include "structure.hpp"

#define NUMCHARS 27
#define APOSTROPHE 39
#define APOSTROPHEINDEX 26
#define ASCIIDEC 32
#define CAPITALLETTERS 96

using namespace std;

void * producer(void * voidPtr)
{
  SHARED_DATA *thisData = (SHARED_DATA *)voidPtr;

  while((thisData->produced->size()) < (thisData->narg))
  {
        //bound check the total produced and then compare to maximum
        if(thisData->produced->size() == thisData->narg)
        {
          //post semaphore for robo semaphore and unlock mutex for consumer threads
          sem_post(thisData->MutexPtr);
          sem_post(thisData->semfullPtr);
          //for only the human driver post the human full semaphore
          if (thisData->Operation == HUMANREQ )
          
          {
            
            sem_post(thisData->hsemfullPtr);
          }
          
          //return statement for the threads
          return nullptr;
        }
      if(thisData->Operation == HUMANREQ)
      {
        //decrement human and robo semaphores and unlock mutex
        sem_wait(thisData->hsememptyPtr);
        sem_wait(thisData->sememptyPtr);
        sem_wait(thisData->MutexPtr);
        
        thisData->requestVal = HumanDriver;
        
        thisData->brokerQueue->push("hreq");
        thisData->queueCount[HumanDriver]++;
        thisData->prodCount[HumanDriver]++;
        io_add_type(thisData->requestVal, thisData->queueCount, thisData->prodCount);
        //increment overall produced vector
        thisData->produced->push_back(producedvariable);

        //increment semaphores and give back mutex
        sem_post(thisData->MutexPtr);
        sem_post(thisData->hsemfullPtr);
        sem_post(thisData->semfullPtr);
        
        
        usleep(USLEEPMULT*thisData->harg);
      }
      else 
      {
        //decrement only robo semaphore and unlock mutex
        sem_wait(thisData->sememptyPtr);
        sem_wait(thisData->MutexPtr);       
        thisData->requestVal = RoboDriver;
        //push the robo command into our queue
        thisData->brokerQueue->push("creq");
        //increment queue size and produced 
        thisData->queueCount[RoboDriver]++;
        thisData->prodCount[RoboDriver]++;
        io_add_type(thisData->requestVal, thisData->queueCount, thisData->prodCount);
        //increment overall produced vector
        thisData->produced->push_back(producedvariable);
        
        //increment semaphores and give back mutex
        sem_post(thisData->MutexPtr);
       
        sem_post(thisData->semfullPtr);
        
        usleep(USLEEPMULT*thisData->aarg);
        
      }
  }
  return nullptr;
}