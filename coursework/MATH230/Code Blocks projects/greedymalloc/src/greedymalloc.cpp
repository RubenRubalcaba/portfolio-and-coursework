#include <stdio.h>
#include <stdlib.h>
int **malloc2d(int r, int c);
int ***malloc3d(int r, int c, int t);
int main()
{
int ** a;
int r,c;
a = malloc2d(3,5);
//printf("size of a is %d bytes \n", sizeof a);
//a[1][3] = 5;
    for(r=0; r<3; r++)
        for(c=0;c<5;c++)
            a[r][c]=0;
		for(r=0; r<3; r++)
		{
			for(c=0;c<5;c++)
			{
				printf(" %d  ", a[r][c]);
            }
            printf( "\n");
        }
return 0;
}
int** malloc2d(int r, int c)
{
int i;
int** t = malloc(r * sizeof(int*));
for (i = 0; i < r; i++)
    t[i] = malloc(c * sizeof(int));
return t;
}
