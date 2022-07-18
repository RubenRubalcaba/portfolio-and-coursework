
#include <stdio.h>
#include <stdlib.h>
#define READ "r"
#define Write "w"
#define FNAME "MIPAcomm.txt"
int main()
{
    int opsum;
    unsigned int machinecode,opcode,shamt,funct,rs,rt,rd;
    char inst, format;
    char * instruction[4]= {"addiu", "liu", "ori", "add"};
    FILE *inputfile;
    if((inputfile = fopen(FNAME,READ)) == NULL )
    {
        printf("Unable to open file to read.\n");
        return 1;
    }

    fscanf(inputfile,"%x", &machinecode);
    printf("Machine Code \topcode \tfunct \t Inst \tFormat \trs \trt \trd \tshamt ");
    opcode = machinecode>>26;
    rs = machinecode<<6>>27;
    rt = machinecode<<11>>27;
    funct = machinecode<<26>>26;
    shamt = machinecode<<21>>27;
    rd = machinecode;
    if(opcode != 0)
    {
        format = "I";
    }
    else if(opcode == 0)
    {
        format = "R";

    }
}





   // */
