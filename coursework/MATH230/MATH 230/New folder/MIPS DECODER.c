
#include <stdio.h>
#include <stdlib.h>
#define READ "r"
#define Write "w"
#define WRITE_F "writefile.txt"
#define FNAME "MIPScomm.txt"
int main()
{
    FILE *writefile;
    int opsum;
    unsigned int machinecode,opcode,shamt,funct,rs,rt,rd,imm;
    char inst, format;
    char *instruction[4][20]= {"addiu", "liu", "ori", "add"};
    FILE *inputfile;
    if((inputfile = fopen(FNAME,READ)) == NULL )
    {
        printf("Unable to open file to read.\n");
        return 1;
    }
   // if((writefile =fopen(WRITE_F,Write)) == NULL)
   // {
   //     printf("Unable to open file to write.\n");
   //     return;
    //}
   // fscanf(inputfile,"%08x", &machinecode);
    printf("Machine Code \topcode \tfunct \t Inst \tFormat \t  rs \trt \trd \tshamt\t Imm\n ");
    fscanf(inputfile,"%08x", &machinecode);
//    fprintf(outputfile,"     .8x", machinecode);
    //while(!feof(inputfile))
    //{
        opcode = machinecode>>26;
        rs = machinecode<<6>>27;
        rt = machinecode<<11>>27;
        funct = machinecode<<26>>26;
        shamt = machinecode<<21>>27;
        rd = machinecode<<16>>27;
        imm = machinecode & 0xFFFF;
       printf(" %.8x", machinecode);

        printf(" \t     %x", opcode);
        if(opcode != 0)
        {
            printf("\t    -\t");
            format = 'I';
            if(opcode == 9)
                inst = &instruction[0];
            else if(opcode > 14)
                inst = &instruction[1];
            else if(opcode > 9)
                inst = &instruction[2];

        }
        else if(opcode == 0)
        {
            format = 'R';
            inst = &instruction[3];
            printf("\t   %x", funct);
            printf("\t");

        }
        printf("%s", inst);
        printf("%13c", format);
        printf("%6u", rs);
        printf("%6u", rt);


        if(format == 'R')
        {

            printf(" \t%u", rd);
            printf(" \t    %u", shamt);
            printf("\t   -");

        }
        else
        {
            printf("\t -\t");
            printf("    -");
            printf("%7.4x", imm);

        }
    printf("\n");
    //}
    fclose(inputfile);
   // fclose(writefile);
}





   // */
