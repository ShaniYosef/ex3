#include "stdio.h"
#include "stdlib.h"
#include <time.h>

#define SIZE 9
#define TURN_NUMBER 12

typedef enum{dead,alive,dntl,lntd} status;  // dead - cell that's dead
                                            // alive - cell that's alive
                                            // dntl - cell that now dead and need to be alive next turn (dead need to live)
                                            // lntd - cell that now alive and need to be dead next turn (live need to dead)




#define REALVAL(x)((((x)%2==0)?dead:alive)) //so we only get 0 if dead and 1 if alive not 2 or 3


//sets the status of each cell
void do_turn(status[][SIZE]);

//sum the neighbors status(1 for living cell 0 for dead one)
int sumNeighbors(int, int ,status[][SIZE]);

//returns what should be the status depends on the current status and neighbors
status setStatus(int,status);

//after finish check what should be the value of each cell change it to alive/dead
void setMat(status[][SIZE]);

//printing the mat
void printMat(status[][SIZE]);

int main(void) {

    int i;
    status mat[SIZE][SIZE] = {0,0,0,0,0,0,0,0,0,
                              0,0,0,0,0,0,0,0,0,
                              0,0,1,1,0,0,0,0,0,
                              0,0,1,0,0,0,0,0,0,
                              0,0,0,0,0,1,0,0,0,
                              0,0,0,0,1,1,0,0,0,
                              0,0,0,0,0,0,0,0,0,
                              0,0,0,0,0,0,0,0,0,
                              0,0,0,0,0,0,1,1,0,};



    for(i=0;i<TURN_NUMBER; i++)
    {
        printf("\tTURN: %d\n",i+1);
        printMat(mat);
        system("PAUSE");
        system("cls");
        do_turn(mat);

    }





    return 0;
}

void do_turn(status mat[SIZE][SIZE])
{
    int i,j;
    for(i =0;i<SIZE;i++)
    {
        for(j=0;j<SIZE;j++)
        {
            mat[i][j]= setStatus(sumNeighbors(i,j,mat), mat[i][j]);
        }
    }

    setMat(mat);


}

int sumNeighbors(int rowIndex, int colIndex,status mat[SIZE][SIZE])
{
    int sum = 0, add2col, add2row;
    int i,j;

    if (rowIndex%(SIZE-1)==0 && colIndex%(SIZE-1)== 0) // connors
    {
        add2row = (rowIndex==0)?1:-1;
        add2col = (colIndex==0)?1:-1;

        sum += REALVAL(mat[rowIndex+add2row][colIndex+add2col]);
        sum += REALVAL(mat[rowIndex+add2row][colIndex]);
        sum += REALVAL(mat[rowIndex][colIndex+add2col]);
        return sum;
    }



    if(rowIndex%(SIZE-1)==0) // top/bottom edge
    {
        add2row = (rowIndex == 0) ? 1 : -1;
        for (i = rowIndex; i != rowIndex + (2 * add2row); i += add2row)
        {
            for (j = colIndex - 1; j <= colIndex + 1; j++)
            {
                if (!(i == rowIndex && j == colIndex))
                {
                    sum += REALVAL(mat[i][j]);
                }
            }
        }
        return sum;

    }

    if(colIndex%(SIZE-1)==0) // left/right edge
    {
        add2col = (colIndex == 0) ? 1 : -1;

        for (i = rowIndex - 1; i <= rowIndex + 1; i++)
        {
            for (j = colIndex; j != colIndex + (2 * add2col); j += add2col)
            {
                if (!(i == rowIndex && j == colIndex))
                {
                    sum += REALVAL(mat[i][j]);
                }
            }
        }
        return sum;
    }


    //all the rest
    for(i = rowIndex-1;i<=rowIndex+1;i++)
    {
        for(j=colIndex-1;j<=colIndex+1;j++)
        {
            if(!(i==rowIndex&&j==colIndex))
            {
                sum += REALVAL(mat[i][j]);
            }
        }
    }


    return sum;

}

status setStatus(int sum,status currentStatus)
{
    if(currentStatus == dead && sum == 3)
        return dntl;
    if(currentStatus == alive && sum >=2 && sum <=3)
        return alive;
    else
        return  (currentStatus==alive?lntd:dead);

}

void setMat(status mat[SIZE][SIZE])
{
    int i,j;
    status curr;
    for(i =0;i<SIZE;i++)
    {
        for(j=0;j<SIZE;j++)
        {
            curr = mat[i][j];
            mat[i][j] = (curr==lntd?dead: curr==dntl?alive:curr);
        }
    }
}


void printMat(status mat[][SIZE])
{
    int i,j;
    for(i =0;i<SIZE;i++)
    {
        for(j=0;j<SIZE;j++)
        {
            printf("%c", mat[i][j]==alive?'o':' ');
        }
        printf("\n");
    }
}