
#include <stdio.h>
#include <stdlib.h>
#define READ "r"
#define Write "w"
#define FNAME "hexinstruction.txt"
int main()
{
    int opcode;
    int opsum;
    unsigned int machinecode, machinehex = 0;
    FILE *inputfile;
    if((inputfile = fopen(FNAME,READ)) == NULL )
    {
        printf("Unable to open file to read.\n")
        return;
    }

    fscanf("%x", &machinehex);
    while)(machinehex != 0 )
    {
       machinecode = machinehex % 2;
       machinehex /= 2;
    }
    opcode = machinecode >>26;
    if(opcode == 0)
    {
        //find shamt and funct and back end of command

    }
    else if(opcode != 0)
    {
        //find rs and rt find address
    }




    */
