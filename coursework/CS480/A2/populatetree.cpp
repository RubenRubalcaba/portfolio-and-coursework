#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;
#include "populatetree.hpp"
void insert(struct dictNode *root,string word){
    struct dictNode *begin = root;
    for (int j = 0; j < word.length();j++)
    {
        if(word[j] != 39)
        {
            word[j] = tolower(word[j]);
        }


    }
    for (int i = 0;i < word.length(); i++)
    {
        int idx = 0;
        idx = word[i]-'a';
        if(word[i] == 39)
        {
            idx = 26;
        }
        if(begin->next[idx]==nullptr)
        {

            dictNode *newnode = new dictNode;
            newnode->isWord = false;
            for (int i = 0;i<NUMOfCHARS;i++)
            {
                //allocate all children to be Null
                newnode->next[i] = NULL;
                begin->next[idx] = newnode;

            }
            
            
        }
        
        begin = begin->next[idx];
    }
    
    begin->isWord = true;
}
//entry into next file
void *popfunction(void *argument){
    EXEC_STATUS *popthread = (EXEC_STATUS*)argument;
    
    string words;
    ifstream input(popthread->filePath[DICTSRCFILEINDEX]);
    string lineread;
        //bad file check
    if(input == NULL)
    {
    cout<<"Unable to open <<"<<popthread->filePath[DICTSRCFILEINDEX]<<">>"<<endl;
    exit(EXIT_FAILURE);
    }
    const char *delimiters = "\n\r  !\"#$%&()*+,-./0123456789:;<=>?@[\\]^_`{|}~";
    while (getline(input,lineread))
        {
            char *arr = new char[lineread.length()+1];
            strcpy(arr,lineread.c_str());
            char* wordd = strtok(arr,delimiters);
            while(wordd != nullptr){
                
                popthread->wordCountInFile[0]+=1;
                insert(popthread->root,wordd);
                wordd = strtok(NULL,delimiters);
            }
            //add line length with terminating character
            *popthread->numOfCharsProcessedFromFile[DICTSRCFILEINDEX] += (double)(lineread.length()+1);
            
            
        }  
        
        
       
    input.close();
   
    pthread_exit(NULL);
    return NULL;
}