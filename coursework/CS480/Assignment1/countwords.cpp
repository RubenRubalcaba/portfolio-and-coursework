/*
Ruben Rubalcaba 
cs480 
Professor Shen
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string.h>
#include <strstream>
#include <sstream>
#define NUMOfCHARS 27 /* a-z plus ' */ 
using namespace std;
//using std::string;
#define NUMOfCHARS 27 /* a-z plus ' */ 
struct dictNode
{    
// isWord is true if the node represents the  
// last character of a word  
    bool isWord; 
 
// Collection of nodes that represent subsequent characters in 
// words. Each node in the next dictNode*  
// array corresponds to a particular character that continues  
// the word if the node at the array index is NOT NULL: 
// e.g., if next[0] is NOT NULL, it means ‘a’ would be  
// one of the next characters that continues the current word; 
// while next[0] being NULL means there are no further words  
// with the next letter as ‘a’ along this path. 
    struct dictNode *next[NUMOfCHARS];  
};
struct dictNode *buildNode(){
    struct dictNode *curnode = new dictNode();
    curnode -> isWord = false;
    for (int i = 0;i<NUMOfCHARS;i++){
        //allocate all children to be Null
        curnode->next[i] = NULL;
    }
    return curnode;
}


void insert(struct dictNode *root,std::string word){
    struct dictNode *begin = root;
    for (int j = 0; j < word.length();j++)
    {
        if(word[j] != 39){
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

            begin->next[idx] = buildNode();
            
        }
        
        begin = begin->next[idx];
    }
    
    begin->isWord = true;
}
bool search(struct dictNode *root,std::string searchword)
{
    struct dictNode *searcher = root;
    for (int j = 0; j < searchword.length();j++)
    {
        if(searchword[j] != 39)
        {
            searchword[j] = tolower(searchword[j]);
        }
        
    }
        

    for (int i = 0;i<searchword.length();i++)
    {
        int index = searchword[i]-'a';
        if(searchword[i] == 39)
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

    if(root->isWord){
        result+=1;
    }
    for (int i = 0; i<NUMOfCHARS; i++)
    {
        if(root->next[i]){

            result+=recurcount(root->next[i]);
        
        }
    }
    return result;

}
void counter(struct dictNode *root,string word)
{  
    int result = 0;
    struct dictNode *countNode = root;
    int count = 0;
    int idx = 0;
    if (!search(countNode,word))
    {
        std::cout<<word<<" "<<result<<"\n";
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
    std::cout<<word<<" "<<count<<"\n";

}


int main(int argc, char **argv){
    string words,words2;
    std::ifstream input(argv[1]);
    string lineread,lineread2;
    std::ifstream input2(argv[2]);
    dictNode *root = new dictNode();
    const char *delimiters = "\n\r  !\"#$%&()*+,-./0123456789:;<=>?@[\\]^_`{|}~";
    if (argc==3){
        while (std::getline(input,lineread))
        {
            char *arr = new char[lineread.length()];
            strcpy(arr,lineread.c_str());
            char* wordd = strtok(arr,delimiters);
            while(wordd != nullptr){
                insert(root,wordd);
                wordd = strtok(NULL,delimiters);
            }
            
        }
        
        input.close();
    
    //read test file 2
    
        while (std::getline(input2,lineread2))
        {
            char *arr2 = new char[lineread2.length()];
            strcpy(arr2,lineread2.c_str());
            char* wordd2 = strtok(arr2,delimiters);
            while(wordd2 != nullptr){
                counter(root,wordd2);
                wordd2 = strtok(NULL,delimiters);
            }
            
        }
        
        input2.close();
    }
    
    else
    {
        cout<<"Error"<<endl;
        exit(EXIT_FAILURE);
    }
        
} 
