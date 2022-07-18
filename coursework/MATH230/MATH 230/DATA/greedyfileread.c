/*
Ruben Rubalcaba
Instructor: Professor: Mimi Rasky
October 23, 2019
Math 230-03
Lab #6
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define READ "r"
int ROWS = 0;
int COLS = 0;
#define FNAME "small data for Lab 6.txt"
int **malloc2d(int r, int c);
void calcSums(int **topog, int *sumList );
int main()
{

    //Allocate 2D Pointer array
    int **array;
    int row, cols,mincost, sumrow, minposition = 0;
    //File pointer

    FILE * inputfile;
    int * sum;

    //Making sure file is open
    if((inputfile = fopen(FNAME, READ)) == NULL)
    {
        return 1;
    }

    //allocating value of ROWS & COLS to
    fscanf(inputfile, "%d%d", &ROWS, &COLS);

    //malloc a 2D array with size of file
    array = malloc2d(ROWS,COLS);

    sum = malloc(ROWS * sizeof (int));

    // nested for loop to put file values into malloc 2D array
    for(row = 0; row < ROWS; row++)
    {
        for(cols = 0; cols< COLS; cols++)
        {
            fscanf(inputfile, "%d", &array[row][cols]);
        }
    }
    //calc sums method call
    calcSums(array, sum);



    mincost = sum[0];

    //For loop to find smallest sum
    for( sumrow = 3; sumrow < ROWS; sumrow++)
    {
        if(mincost > sum[sumrow])
        {
            mincost = sum[sumrow];
            minposition = sumrow;
        }

    }
    //Print statements
    printf("The number of rows is: %d", ROWS);

    printf("\nThe number of columns is: %d\n", COLS);

    printf("\nThe minimum cost is: %d\n", mincost);

    printf("The minimum row is : %d\n", minposition);



    fclose(inputfile);
    return 0;
}
int ** malloc2d(int r, int c)
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
void calcSums(int **topog, int *sums )
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

           //If statement to begin at first row
           if( rowval == 0 )
           {
               middle_row = abs(topog[rowval][col + 1] - topog [rowval][col]);

               bottom_row = abs(topog[rowval + 1][col + 1] - topog[rowval][col]);

               if(bottom_row < middle_row)

                   nextrow  = rowval + 1;


               else if(middle_row <= bottom_row)

                   nextrow = rowval;



           }
           //If statement for any non-top or bottom row start.
           else if( rowval != ROWS - 1)
           {
               //initialization of rows done within for loop to make sure malloc array does not overflow
               top_row = abs(topog[rowval - 1][col + 1] - topog[rowval][col] );

               middle_row = abs(topog[rowval][col + 1] - topog [rowval][col]);

               bottom_row = abs(topog[rowval + 1][col + 1] - topog[rowval][col]);

               //if top row is the least between the other two choices
               if(top_row < middle_row && top_row < bottom_row)

                   nextrow = rowval - 1;

               //if bottom row is less than top and middle
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
               top_row = abs(topog[rowval - 1][col + 1] - topog[rowval][col] );

               middle_row = abs(topog[rowval][col + 1] - topog [rowval][col]);


               if(top_row < middle_row)

                   nextrow = rowval - 1;

               else if(middle_row == top_row || middle_row < top_row)

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
