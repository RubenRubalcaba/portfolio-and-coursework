#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;
#include "countwords.hpp"
#include <mutex>
#include <thread>
std::ofstream file("countwords_output.txt");


bool search(struct dictNode *root,string searchword)
{
    string temp = searchword;
    dictNode *searcher = root;
    for (int j = 0; j < temp.length();j++)
    {
        if(temp[j] != 39)
        {
            temp[j] = tolower(searchword[j]);
        }
        
    }
        

    for (int i = 0;i<temp.length();i++)
    {
        int index = temp[i]-'a';
        if(temp[i] == 39)
        {
            index = 26;
        }
        if (searcher->next[index]==nullptr)
        {
            return false;

        }
        
        searcher = searcher->next[index];
        
    }
    return true;
}
int recurcount(struct dictNode *root){
    int result = 0;
    struct dictNode *counter = root;
    int i = 0;
    if(root->isWord)
    {
        result+=1;
    }
    //move throughout the children to check for 
    while (i < NUMOfCHARS )
    {
           if(counter->next[i])
        {
            result+=recurcount(counter->next[i]);       
        }
        i++;
    }
    //base case hit no more children and return
    return result;

}
void counter(struct dictNode *root,string word,int minimum)
{  
    int result = 0;
    struct dictNode *countNode = root;
    int count = 0;
    int idx = 0;
    //search method used if word is found in tree to see and if not then just print and move on.
    if (!search(countNode,word))
    {
        return;
        
        
    }
    else
    {
        for (int j = 0; j < word.length();j++)
        {
            if(word[j] != 39)
            {
                word[j] = tolower(word[j]);
            }
        
        }
        
        for (int i = 0;i<word.length();i++)
        {
            int index = word[i]-'a';
            if(word[i] == 39)
            {
                index = 26;
            }
            countNode = countNode->next[index];   
        }

            count += recurcount(countNode);


        }   
        //after base case in countrecur hit then print word with the count
        if (count >= minimum ){

            file <<word<<" "<<count<<std::endl;
        }
        

    }




void* countfunct(void *argument){
    EXEC_STATUS *countwordsthread = (EXEC_STATUS*)argument;
    string words,lineread;
    ifstream input(countwordsthread->filePath[TESTFILEINDEX]);

    //bad file check
    // if(input = NULL){
    //     cout<<"Unable to open <<"<<countwordsthread->filePath[TESTFILEINDEX]<<">>"<<endl;
    //     exit(EXIT_FAILURE);
    // }



    int countering = 0;
    const char *delimiters = "\n\r  !\"#$%&()*+,-./0123456789:;<=>?@[\\]^_`{|}~";
    while (!countwordsthread->taskCompleted[DICTSRCFILEINDEX])
    {
        //do nothing
    }

     while (getline(input,lineread))
    {
        char *arr2 = new char[lineread.length()+1];
        strcpy(arr2,lineread.c_str());
        char* wordd2 = strtok(arr2,delimiters);
        
        while(wordd2 != nullptr)
            {
            countwordsthread->wordCountInFile[TESTFILEINDEX]+=1;
            countering+=1;
            counter(countwordsthread->root,wordd2,countwordsthread->minNumOfWordsWithAPrefixForPrinting);
            wordd2 = strtok(NULL,delimiters);
            
            }
        
       *countwordsthread->numOfCharsProcessedFromFile[TESTFILEINDEX] += (double)(lineread.length()+1);


            
    }
    
     
    input.close();
    file.close();   
    

    pthread_exit(NULL);
    return NULL;
}