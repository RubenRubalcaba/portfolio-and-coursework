#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <cstring>
#include <cctype>
#include <fstream>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <cmath>
using namespace std;
#define NUMOFFILES 2 
#define DICTSRCFILEINDEX 0 
#define TESTFILEINDEX 1 
#define NUMOfCHARS 27 /* a-z plus ' */ 
/* default number of progress marks for representing 100% progress */ 
#define DEFAULT_NUMOF_MARKS 50 
 
/* minimum number of progress marks for representing 100% progress */ 
#define MIN_NUMOF_MARKS 10 
 
/* place hash marks in the progress bar every N marks */ 
#define DEFAULT_HASHMARKINTERVAL  10 
 
/* default minimum number of dictionary words starting from a prefix for printing or 
writing to the output */ 
#define DEFAULT_MINNUM_OFWORDS_WITHAPREFIX  1
#ifndef dict
#define dict
struct dictNode
{  
    bool isWord; 
    struct dictNode *next[NUMOfCHARS];  
};

#endif
#ifndef EXECSTATUS
#define EXECSTATUS
struct EXEC_STATUS { 

    struct dictNode *root; 
    int numOfProgressMarks; 
    int hashmarkInterval; 
 

    int minNumOfWordsWithAPrefixForPrinting;  
    long  *numOfCharsProcessedFromFile[NUMOFFILES]; 

    const char  *filePath[NUMOFFILES]; 
    long  totalNumOfCharsInFile[NUMOFFILES]; 
    long  wordCountInFile[NUMOFFILES]; 
    bool  taskCompleted[NUMOFFILES];  
};
#endif
