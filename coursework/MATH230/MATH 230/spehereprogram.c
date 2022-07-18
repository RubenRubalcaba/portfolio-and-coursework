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
    for(r = 0; r < 3; r++)
        for(c = 0;c < 5;c++)
            a[r][c]=0;
		for(r=0; r<3; r++)
		{
			for(c = 0;c < 5;c++)
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
/*
 *  Receives 2d matrix that represents topography
 *  and uses this data to calculate an elevation path sum for each
 *  row.
 *  Input:  topog[][]
 *  Output: sum[]
 */
void calcSums(int topog[ROWS][COLS], int sums[ROWS] )
{
    int nextrow = 0;
    int rowval, col, coinflip;
    int top_row = 0;
    int middle_row = 0;
    int bottom_row = 0;
    int r = 0;
    srand(time(NULL));
    for(rowval = 0; rowval < ROWS; rowval++)
    {

        for(col = 0; col < COLS - 1; col++)
        {
            //absolute value function calculating middle row difference
            top_row = abs(topog[rowval - 1][col + 1] - topog[rowval][col] );

            middle_row = abs(topog[rowval][col + 1] - topog [rowval][col]);

            bottom_row = abs(topog[rowval + 1][col + 1] - topog[rowval][col]);
           //If statement to begin at first row
           if( rowval == 0 )
           {

               if(middle_row < bottom_row)

                    nextrow = rowval;


               else if(bottom_row < middle_row)

                   nextrow  = rowval + 1;


               else if(middle_row == bottom_row)

                   nextrow = rowval;



           }
           //If statement for any non-top or bottom row start.
           else if( rowval != ROWS - 1)
           {

               if(top_row < middle_row && top_row < bottom_row)

                   nextrow = rowval - 1;

               else if(bottom_row < top_row && bottom_row < middle_row)

                   nextrow = rowval + 1;

               else if(middle_row < top_row && middle_row < bottom_row)

                   nextrow = rowval;

               else if(middle_row == top_row || middle_row == bottom_row)

                   nextrow = rowval;

               else if(top_row == bottom_row)
               {
                   //Coin flip using rand and modulo function
                   coinflip = rand() % 2;
                   //Random remainder picks either the top row or bottom
                   if(coinflip == 0 )

                       nextrow = rowval - 1;

                   else

                       nextrow = rowval + 1;

               }



           }
           //Else if starting at bottom row
           else if( rowval == ROWS - 1)
           {

               if(top_row < middle_row)

                   nextrow = rowval - 1;

               else if (middle_row < top_row)

                   nextrow = rowval;

               else if(middle_row == top_row)

                   nextrow = rowval;


           }
           //Add statement for each row to be added into array of sums
           if( nextrow == rowval)

               sums[r] += middle_row;

           else if(nextrow == rowval - 1 )

               sums[r] += top_row;

           else if(nextrow == rowval + 1)

               sums[r] += bottom_row;

           // rowval moves to what row was picked
           rowval = nextrow;

        }
        //rowval goes back to next starting row
        rowval = r;
        //Increment to next position in the next sum row
        r++;

    }

}
