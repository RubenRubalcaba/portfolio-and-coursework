
#include "consumer.hpp"
#include "structure.hpp"

#define NUMCHARS 27
#define APOSTROPHE 39
#define APOSTROPHEINDEX 26
#define ASCIIDEC 32
#define CAPITALLETTERS 96

using namespace std;

void* consumer(void * voidPtr)
{
  SHARED_DATA *thisData = (SHARED_DATA *)voidPtr;
  
  while((thisData->consumed->size()) < (thisData->narg))
  {  
      if(thisData->Operation == FASTMATCH)
      {
        ConsumerType algoType = FastAlgoDispatch;
        RequestType consumedReq;
        //decerment semaphore and unlock mutex
        sem_wait(thisData->semfullPtr);    
        sem_wait(thisData->MutexPtr);
        
        if ((thisData->brokerQueue->front()) == "hreq")
        {
          consumedReq = HumanDriver;
          //decrement human semaphore
          sem_wait(thisData->hsemfullPtr);
          //increment fast human array
          thisData->fastalgo[consumedReq]++;
        }
        else
        {
          //increment robo array
          consumedReq = RoboDriver;
          thisData->fastalgo[consumedReq]++;
        }
        thisData->brokerQueue->pop();
        thisData->queueCount[consumedReq]--;
         
        io_remove_type(algoType, consumedReq, thisData->queueCount, thisData->fastalgo);
        thisData->consumed->push_back(consumedval);   
        
        //increment semaphores and mtuex
        sem_post(thisData->MutexPtr);
        sem_post(thisData->hsememptyPtr);
        sem_post(thisData->sememptyPtr);
        
        
        usleep(USLEEPMULT*thisData->farg);
      }
      else if(thisData->Operation == COSTSAVE)
      {
        ConsumerType algoType = CostAlgoDispatch;
        RequestType consumedReq;
        //decerment semaphore and unlock mutex
        sem_wait(thisData->semfullPtr);    
        sem_wait(thisData->MutexPtr);
        if ((thisData->brokerQueue->front()) == "hreq")
        {
          consumedReq = HumanDriver;
          //decrement human semaphore
          sem_wait(thisData->hsemfullPtr);
          thisData->costalgo[consumedReq]++;
        }
        else
        {
          //increment robo array
          consumedReq = RoboDriver;
          thisData->costalgo[consumedReq]++;
        }
        thisData->brokerQueue->pop();
        thisData->queueCount[consumedReq]--;
         
        io_remove_type(algoType, consumedReq, thisData->queueCount, thisData->costalgo);
        thisData->consumed->push_back(consumedval);   
        

        //increment semaphores and mtuex
        sem_post(thisData->MutexPtr);
        sem_post(thisData->hsememptyPtr);
        sem_post(thisData->sememptyPtr);
        
        
        usleep(USLEEPMULT*thisData->carg);
      }
      usleep(1);
  } 
  return nullptr;
}