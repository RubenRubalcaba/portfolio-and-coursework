#include <vector>
#include <iostream>
#include <fstream>
#include <cstring>
#include <stdio.h>
#include <pthread.h>
#include <sched.h>
#include <unistd.h>
#include <pthread.h>
#include <unistd.h>
 
#include <cmath>
#include <iomanip>
#include <semaphore.h>
#include <stdlib.h>
#include <queue>

#include "io.h"
#include "ridesharing.h"
#define producedvariable 1
#define consumedval 1
#define DEFAULTNARG 120
#define DEFAULTARGVAL 0
#define USLEEPMULT 1000
#define SEMAPHOREMAX 12
#define SEMAPHOREHUMANMAX 4

#ifndef consuming
#define consuming

using namespace std;

typedef enum
{
    HUMANREQ,
    COMPREQ,
    FASTMATCH,
    COSTSAVE
} OPERATION;

struct consumering
{
    int fastCount[ConsumerTypeN]; //fast counter
    int costCount[ConsumerTypeN]; //cost counter
    int prodcount[RequestTypeN];
    
};
struct SHARED_DATA
{
    queue <string> *brokerQueue;
    vector <int> *produced;
    vector <int> *consumed;
    OPERATION Operation;
    
    RequestType requestVal;
    

  
    int temp;
    
    int narg = DEFAULTNARG;
    int carg = DEFAULTARGVAL;
    int farg = DEFAULTARGVAL;
    int harg = DEFAULTARGVAL;
    int aarg = DEFAULTARGVAL;
    
    
    sem_t *sememptyPtr;
    sem_t *semfullPtr;  
    sem_t *MutexPtr;
    sem_t *hsememptyPtr;
    sem_t *hsemfullPtr;
    
    //thread specific variables
    int *queueCount; //in Queue
    int *prodCount; //totalproduce
    
    int *fastalgo;
    int *costalgo;

    
};

#endif