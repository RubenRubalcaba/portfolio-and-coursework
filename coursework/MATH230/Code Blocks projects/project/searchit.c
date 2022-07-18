/*
Ruben Rubalcaba
Instructor: Professor Mimi Rasky
Math 230-03
October 1,2019
*/
#include <stdio.h>
#include <stdlib.h>
char * searchit(char *str, int str_size, char ref_char);
int main()
{
    int i;
    char character;
    char string[100];
    printf("Please enter a string:");
    scanf("%[^\n]s",&string);
    printf("Please enter a character to search for: ");
    scanf(" %c",&character);
    printf("The string is: %s", string);
    searchit(string, sizeof(string)/sizeof(char), character);
    return 0;
}
char * searchit(char *string, int str_size, char ref_char)
{
    int j,k;
    char ref = ref_char;
    char * loc = &string[0];
    printf("\n");
    for( j = 0; j < str_size; j++ )
    {
      if(string[j] ==  ref)
      {
          loc = &string[j];
      }

    }


    if(*loc == ref_char)
    {
        printf("%c was found in the string", ref);
        printf("\nThe string beginning at %c is: %s", ref, loc);

    }


    else
    {
        printf("%c was not found in the string", ref);
        loc = &string[j];

    }
    printf("\n");
    printf("Address \tContents\t ASCII\n");
    for(k = 0; k<sizeof(loc) / sizeof(char) ;k++)
    {
        if(loc[k] == 32)
        {
          k++;
        }
        printf("%p\t0x%02x\t%c", loc[k],loc[k],loc[k]);
        printf("\n");
    }


    return loc;
}
