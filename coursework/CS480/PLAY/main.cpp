#include <iostream>
#include "io.h"

using namespace std;




int main(int argc, char **argv){
    int opt;
    int narg = 120;
    int carg = 0;
    int farg = 0;
    int harg = 0;
    int aarg = 0;
    int tempnum;
    while ((opt = getopt(argc,argv,"n:c:f:h:a:")) != -1)
    {
        switch (opt)
        {
            case (int)'n':
            {
                tempnum = atoi(optarg);
                narg = tempnum;
                continue;

            }
            case (int)'c':
            {
                tempnum = atoi(optarg);
                carg = tempnum;
                continue;
            }
            case (int)'f':
            {
                tempnum = atoi(optarg);
                farg = tempnum;
                continue;
            
            }
            case (int)'h':
            {
                tempnum = atoi(optarg);
                harg = tempnum;
                continue;
            }            
            case(int)'a':
            {
                tempnum = atoi(optarg);
                aarg = tempnum;
                continue;
            }
            
        
        
            
        }
        break;
    }
    
    
    
    return 0; 

}