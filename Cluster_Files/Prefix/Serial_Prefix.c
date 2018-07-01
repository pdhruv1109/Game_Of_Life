/*---------------------------------------------
Serial implementation of Prefix Approach
Author:  201501452 - Dhruv Patel
	 201501408 - Raj Jakasaniya
---------------------------------------------*/


#include <stdio.h>						/* including the header */
#include <omp.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int **curr;							/* making gobal 2D array */
int **next;
int **prefix;


void print(int row,int col)					/* function for printing output martix which take no. of row and no. of column as parameter */
{
	int i, j;
	for (i = 0; i < row; ++i)				
	{
		for (j = 0; j < col; ++j)
		{
			printf("%d ",curr[i][j]);		/* printing status dead(0) or alive(1) */
		}
		printf("\n");
	}
	printf("\n");
}

void prefix_sum(int row,int col)				/* this function calculates the no. of cells alive in the grid (row,col), here the row and col are parameters */
{
    int x,y;
    for(x=2;x<row;x++)						/* here we have started for loop from 2 because we have given padding of 2  */
    {
        for(y=2;y<col;y++)
        {
            prefix[x][y] = curr[x][y] - prefix[x-1][y-1] + prefix[x-1][y] + prefix[x][y-1];		/* this equation gives the no. of live cells in grid (x,y) */
        }
    }
}

void change(int row,int col)					/*  this function change the state of cell according to the rules */
{
    prefix_sum(row,col);					/*  calling prefix_sum function  */
    int x,y;
    for(x=2;x<row-1;x++)					/* here we have started for loop from 2 because we have given padding of 2  */
    {
        for(y=2;y<col-1;y++)
        {
            
            int live = prefix[x+1][y+1] - prefix[x-2][y+1] - prefix[x+1][y-2] + prefix[x-2][y-2] - curr[x][y];		/*  this equation gives the no. of neighbours alive of cell (x,y)  */
            int state = curr[x][y];
            
            next[x][y] = state;

            if(state==1 && (live<2 || live>3))			/*  if the cell is live and it is underpopulated or overpopulated then it dies  */
            {
                next[x][y]=0;					/*  changing state from alive to dead  */
            }
            
            if(state==0 && live==3){				/*  if cell is dead and the no. of neighbours alive is 3 then cell becomes alive */ 
                next[x][y]=1;					/*  changing state from dead to alive  */
            } 
        }
    }

    for(x=2;x<row-1;x++){					/* coping new status matrix to curr matrix  */
        for(y=2;y<col-1;y++){
            curr[x][y]=next[x][y];
        }
    }
}

int main(int argc , char** argv)				/* taking arguments for matrix size and no. of steps  */
{

    int i,j,row,col,t_steps,steps;				/*  initialising the variable  */
    double start,stop;
    float x;

    row=atoi(argv[1]);						/* initialising the no. of rows, column, and no. of steps from arguments */
    col=atoi(argv[2]);
    t_steps=atoi(argv[3]);

    curr=(int **)(malloc((row+4)*sizeof(int *)));		/* allocatting the memory of row using malloc  */
    next=(int **)(malloc((row+4)*sizeof(int *)));
    prefix=(int **)(malloc((row+4)*sizeof(int *)));
    for(i=0;i<(row+4);i++)
    {
        curr[i]=(int *)(malloc((col+4)*sizeof(int)));		/* allocatting the memory of column using malloc  */
        next[i]=(int *)(malloc((col+4)*sizeof(int)));
        prefix[i]=(int *)(malloc((col+4)*sizeof(int)));
        for(j=0;j<(col+4);j++)					/*  generating the random input  */
        {
            if(i<2 || j<2 || i>(row+1) || j>(col+1)){
                curr[i][j]=0;
            }else{
                curr[i][j]=rand()%2;
            }
            prefix[i][j]=0;
            next[i][j]=0;
        }
    }
    

    start = omp_get_wtime();				/* calculating the time  */

    for(steps=0;steps<t_steps;steps++)			/* for loop iterating till no. of steps  */
    {
        //print(row+4,col+4);
        change(row+4,col+4);
        //print(row+4,col+4);
    } 

    //print(row+4,col+4);    
    
    stop = omp_get_wtime();

    char file_name[100];

    strcpy(file_name, "Serial_Prefix.txt");
    FILE* fp = fopen(file_name, "a+");			/* opening a file  */
    
    fprintf(fp,"%0.10lf\n", (stop-start));		/* writing time in file  */
}
