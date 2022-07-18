/* Ramon De Dios
Ruben Rubalcaba
Professor Ben Shen
CS 480
04/21/2022
main.cpp
*/
#include "structure.hpp"
#include "io.h"
#include "ridesharing.h"
#include "consumer.hpp"
#include "producer.hpp"

using namespace std;

int main(int argc, char **argv)
{ 
  //variable declaration to catch both mandatory and optional arguments.
  int opt;
  int tempNum;
  
  int qCount[RequestTypeN] = {0,0}; //in Queue
  int pCount[RequestTypeN] = {0,0}; //totalproduce
  
  int hCount[RequestTypeN] = {0,0}; //human counter for inside consumer
  int cCount[RequestTypeN] = {0,0}; //computer counter for inside consumer
    
  int currProd = 0;
  int currCons = 0;
    
  //queue intialization
  queue <string> BUFF;
  vector <int> tempvec;
  vector<int> tempconsum;
    
  std::string oarg = "";
  //quad object initialization with main buffer to reference
  struct consumering *construction = new consumering;

  struct SHARED_DATA *humanData = new SHARED_DATA();
  pthread_t humanProducerThread;
  struct SHARED_DATA *compData = new SHARED_DATA();
  pthread_t compProducerThread;
  
  struct SHARED_DATA *fastMatchData = new SHARED_DATA();
  pthread_t fastMatchThread;
  struct SHARED_DATA *costsaveData = new SHARED_DATA();
  pthread_t costsaveThread;

  sem_t Mutex;
  sem_t semempty;
  sem_t semfull;  
  sem_t humanempty; 
  sem_t humanfull;
  
  //shared initilization for semaphores
  humanData->MutexPtr = &Mutex;
  compData->MutexPtr = &Mutex;
  fastMatchData->MutexPtr = &Mutex;
  costsaveData->MutexPtr = &Mutex;
  humanData->sememptyPtr = &semempty;
  compData->sememptyPtr = &semempty;
  fastMatchData->sememptyPtr = &semempty;
  costsaveData->sememptyPtr = &semempty;
  humanData->semfullPtr = &semfull;
  compData->semfullPtr = &semfull;
  fastMatchData->semfullPtr = &semfull;
  costsaveData->semfullPtr = &semfull;
  humanData->hsememptyPtr = &humanempty;
  compData->hsememptyPtr = &humanempty;
  fastMatchData->hsememptyPtr = &humanempty;
  costsaveData->hsememptyPtr = &humanempty;
  humanData->hsemfullPtr = &humanfull;
  compData->hsemfullPtr = &humanfull;
  fastMatchData->hsemfullPtr = &humanfull;
  costsaveData->hsemfullPtr = &humanfull;
  
  //buffer address initialization
  humanData->brokerQueue = &BUFF;
  compData->brokerQueue = &BUFF;
  fastMatchData->brokerQueue = &BUFF;
  costsaveData->brokerQueue = &BUFF;
  
  //OPERATION initialization
  humanData->Operation = HUMANREQ;
  compData->Operation = COMPREQ;
  fastMatchData->Operation = FASTMATCH;
  costsaveData->Operation = COSTSAVE;
  
  //queue and prod initialization 
  humanData->queueCount = qCount;
  humanData->prodCount = construction->prodcount;
  compData->queueCount = qCount;
  compData->prodCount = construction->prodcount;
  fastMatchData->queueCount = qCount;
  costsaveData->queueCount = qCount;
  
  //fast and cost count initialization
  fastMatchData->fastalgo = construction->fastCount;
  costsaveData->costalgo = construction->costCount;
  //2D array for final production report
  int *consumeCounting[ConsumerTypeN] = {construction->costCount,construction->fastCount};
  //human and comp vector for produced count total
  humanData->produced = &tempvec;
  compData->produced = &tempvec;
  fastMatchData->consumed = &tempconsum;
  costsaveData->consumed = &tempconsum;


  /* The following while loops are responsible for argument grabbing.
  Will grab -n, -c and -o arguments and set them accordingly.
  */
  while((opt = getopt(argc, argv, "n:c:f:h:a:")) != -1) { 
    switch(opt) { 
      case (int)'n': {
        tempNum = atoi(optarg);
        humanData->narg = tempNum;
        compData->narg = tempNum;
        fastMatchData->narg = tempNum;
        costsaveData->narg = tempNum;
        continue; 
      }
      case (int)'c': {
        tempNum = atoi(optarg);
        fastMatchData->carg = tempNum;
        costsaveData->carg = tempNum;
        continue; 
      }
      case (int)'f': {
        tempNum = atoi(optarg);
        fastMatchData->farg = tempNum;
        costsaveData->farg = tempNum;
        continue; 
      }
      case (int)'h': {
        tempNum = atoi(optarg);
        humanData->harg = tempNum;
        compData->harg = tempNum;
        continue; 
      }
      case (int)'a': {
        tempNum = atoi(optarg);
        humanData->aarg = tempNum;
        compData->aarg = tempNum;
        continue; 
      }
    } 
    break;
  }//end of while loop. Optional arguments grabber. 
  
  
  //HUMAN
  //initialization of empty semaphore to increment down 
  sem_init(&Mutex,0,1);
  sem_init(&semempty,0,SEMAPHOREMAX);
  sem_init(&semfull,0,0);
  sem_init(&humanempty,0,SEMAPHOREHUMANMAX);
  sem_init(&humanfull,0,0);
  
  //quad thread initialization 
  pthread_create(&humanProducerThread, NULL, &producer, (void *)humanData);
  pthread_create(&compProducerThread, NULL, &producer, (void *)compData);
  pthread_create(&fastMatchThread, NULL, &consumer, (void *)fastMatchData);
  pthread_create(&costsaveThread, NULL, &consumer, (void *)costsaveData);
  
//main busy waiting action 
  (void)pthread_join(humanProducerThread,NULL);
  (void)pthread_join(compProducerThread,NULL);   
  (void)pthread_join(fastMatchThread,NULL);
  (void)pthread_join(costsaveThread,NULL);
  
  //ending production report print 

  io_production_report(construction->prodcount, consumeCounting);
  
  sem_destroy(&Mutex);
  sem_destroy(&semempty);
  sem_destroy(&semfull);
  sem_destroy(&humanempty);
  sem_destroy(&humanfull);

  
}