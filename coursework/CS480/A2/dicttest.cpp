/*
    Ruben Rubalcba 
    CS 480 
    Professor Shen 
    28 February 2022

*/
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
#include <getopt.h>
#include "populatetree.hpp"
#include "countwords.hpp"
#include "exec.hpp"
using namespace std;

/* Common data shared between threads */ 

int main(int argc, char **argv){
    if (argc>=3){
        int argcount = 0;
        int options = 3;
        double percent = 0;
        struct EXEC_STATUS *start = new EXEC_STATUS();
        start->root = new dictNode();
        start->taskCompleted[DICTSRCFILEINDEX] = false;
        start->taskCompleted[TESTFILEINDEX] = false;
        start->numOfCharsProcessedFromFile[DICTSRCFILEINDEX] = new long();
        start->numOfCharsProcessedFromFile[TESTFILEINDEX] = new long();
        start->hashmarkInterval = DEFAULT_HASHMARKINTERVAL;
        start->numOfProgressMarks = DEFAULT_NUMOF_MARKS;
        start->minNumOfWordsWithAPrefixForPrinting = DEFAULT_MINNUM_OFWORDS_WITHAPREFIX;
        start->taskCompleted[DICTSRCFILEINDEX] = false;
        start->taskCompleted[TESTFILEINDEX] = false;
    
        int perecent_displayed = 0;
        start->filePath[DICTSRCFILEINDEX] = argv[1];
        start->filePath[TESTFILEINDEX] = argv[2];
        
        while ((options = getopt(argc,argv,"p:h:n:")) != 1)
        {
            
            switch (options)
            {
                case (int)'p':
                    
                    if (atoi(optarg) < MIN_NUMOF_MARKS)
                    {
                        cout<<"Number of progress marks must be a number and at least 10";
                        exit(EXIT_FAILURE);
                    }
                    else
                    {
                        start->numOfProgressMarks = atoi(optarg);
                      
                        continue;
                    }
                case (int)'h':
                    if(atoi(optarg)>10 || atoi(optarg) <= 0)
                    {
                        cout<<"Hash mark interval for progress must be a number, greater than 0 ,and less than or equal to 10";
                    }
                    else
                    {
                        start->hashmarkInterval = atoi(optarg);
                        continue;
                        
                    }
                case (int)'n':
                    if (atoi(optarg) <= 0)
                    {
                        continue;
                    }
                    else
                    {
                        start->minNumOfWordsWithAPrefixForPrinting = atoi(optarg);
                       
                        continue;
                    }
                
                
                
                }
                break;
        }
        struct stat testbuf;
        struct stat dictbuf;
        stat(start->filePath[DICTSRCFILEINDEX],&dictbuf);
        stat(start->filePath[TESTFILEINDEX],&testbuf);
            
        start->totalNumOfCharsInFile[DICTSRCFILEINDEX] = dictbuf.st_size;
        start->totalNumOfCharsInFile[TESTFILEINDEX] = testbuf.st_size;

        pthread_t poptree,countingwords;
        
        pthread_create(&poptree,NULL,&popfunction,(void*)start);
        while(!start->taskCompleted[DICTSRCFILEINDEX])
        {

            percent = (double) *start->numOfCharsProcessedFromFile[DICTSRCFILEINDEX] /  (double) start->totalNumOfCharsInFile[DICTSRCFILEINDEX];
        
            if((int)perecent_displayed <= (int)start->numOfProgressMarks)
            {
                
                if(floor((int)perecent_displayed) - (int)(percent * start->numOfProgressMarks) != 0 && perecent_displayed != 0 )
                {
                    if((int)floor(perecent_displayed) %(int)floor(start->hashmarkInterval) == 0)
                    {
                        cout<<"#";
                    }    
                    else
                    {
                        cout<<"-";
                    }
                    
                }
                cout<<flush;
                
            }
                perecent_displayed = floor(percent * start->numOfProgressMarks);
                //keep checking if percent is complete
                if(perecent_displayed >= (int)start->numOfProgressMarks){
                    start->taskCompleted[DICTSRCFILEINDEX] = true;
                    cout<<"#"<<endl;
                }

        }
        //after percent complete is done then automatically print output
        cout<<"There are "<<start->wordCountInFile[DICTSRCFILEINDEX]<<" words "<<" in "<<start->filePath[DICTSRCFILEINDEX]<<"."<<endl;
        
        
    

        //reinitialize percent variables
        perecent_displayed = 0;
        percent = 0.0;
        pthread_create(&countingwords,NULL,&countfunct,(void*)start);
        while(!start->taskCompleted[TESTFILEINDEX])
        {

            percent = (double) *start->numOfCharsProcessedFromFile[TESTFILEINDEX] /  (double) start->totalNumOfCharsInFile[TESTFILEINDEX];
        
            if((int)perecent_displayed <= (int)start->numOfProgressMarks)
            {
                
                if(floor((int)perecent_displayed) - (int)(percent * start->numOfProgressMarks) != 0 && perecent_displayed != 0 )
                {
                    if((int)floor(perecent_displayed) %(int)floor(start->hashmarkInterval) == 0)
                    {
                        cout<<"#";
                    }    
                    else
                    {
                        cout<<"-";
                    }
                    
                }
                cout<<flush;
                
            }
                perecent_displayed = floor(percent * start->numOfProgressMarks);
                if(perecent_displayed >= (int)start->numOfProgressMarks){
                    start->taskCompleted[TESTFILEINDEX] = true;
                    cout<<"#"<<endl;
                }

        }
        //extra boolean flag to make sure test file is complete
        while (!start->taskCompleted[TESTFILEINDEX])
        {
            
        }
        cout<<"There are "<<start->wordCountInFile[TESTFILEINDEX]<<" words "<<" in "<<start->filePath[TESTFILEINDEX]<<"."<<endl;

        
        pthread_exit(NULL);    
        return 0;
        }
    else{
        cout<<"Incorrect number of arguments";
        exit(EXIT_FAILURE);
    }
}



    

    // delete(start->numOfCharsProcessedFromFile[DICTSRCFILEINDEX]);
    // delete(start->numOfCharsProcessedFromFile[TESTFILEINDEX]);
    

//}

