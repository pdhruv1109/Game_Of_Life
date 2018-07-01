/*---------------------------------------------
Serial implementation of Optimised Approach
Author:  201501452 - Dhruv Patel
	 201501408 - Raj Jakasaniya
---------------------------------------------*/

#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int **curr;                 /* making gobal 2D array */
int **next;                 

int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};

int neighbours(int x,int y,int row,int col){        /* this function gives the no. of neighbours alive cell (x,y)  */
    int count=0,temp=0;
    for(temp=0;temp<8;temp++){
        int i=x+dx[temp];
        int j=y+dy[temp];
        
        if(i<0) i=i+row;
        if(j<0) j=j+col;

        if(i>=row) i=i-row;
        if(j>=col) j=j-col;

        count=count+curr[i][j];      
    }
    return count;
}

void print(int row,int col)                     /* function for printing output martix which take no. of row and no. of column as parameter */
{
	int i, j;
	for (i = 0; i < row; ++i)
	{
		for (j = 0; j < col; ++j)
		{
			printf("%d ",curr[i][j]);           /* printing status dead(0) or alive(1) */
		}
		printf("\n");
	}
	printf("\n");
}

void change(int r,int c){                       /* This function is used to change generation's following the rules */
    int i,j,k;
    for(i=1;i<r-1;i++){
        int alive,state,c1=0,c2=0,c3=0;
        j=1;
        
        /* c1,c2 and c3 are variables whose sum gives the number of live cell for a particular cell , value c1,c2 and c3 continously change for every cell */
        
        c1=curr[i][j - 1] + curr[i - 1][j - 1] + curr[i + 1][j - 1];        /* Initializing of c1,c2 and c3 for every row */
        c2=curr[i - 1][j] + curr[i + 1][j];
        c3=curr[i][j + 1] + curr[i - 1][j + 1] + curr[i + 1][j + 1];

        for(j=1;j<c-1;j++){
            alive=c1+c2+c3;

            c2=c2+curr[i][j];                       /* Updating the value of c2 and c3 to use them for next cell*/
            c3=c3-curr[i][j+1];
            
                
            c1=c2;                                  /* finding new c1,c2 and c3 using the old c1,c2 and c3 for next cell */
            c2=c3;
            c3=curr[i - 1][j + 2] + curr[i][j + 2] + curr[i + 1][j + 2];        /* For next cell calculating c3 once again */
    
            state=curr[i][j];
            next[i][j]=state;

            if(state==1 && (alive<2 || alive>3)){           /* Applying Rules on the number of live neighbours and changing state accordingly */
                next[i][j]=0;
            }

            if(state==0 && alive==3){
                next[i][j]=1;
            }
        }
    }

    for(i=0;i<r;i++){                               /* Taking care of first and last column */
        int alive,state;

        alive=neighbours(i,0,r,c);
        state=curr[i][0];
        next[i][0]=state;
        
        if(state==1 && (alive<2 || alive>3)){
            next[i][0]=0;
        }

        if(state==0 && alive==3){
            next[i][0]=1;
        }



        
        alive=neighbours(i,c-1,r,c);
        state=curr[i][c-1];
        next[i][c-1]=state;
        
        if(state==1 && (alive<2 || alive>3)){
            next[i][c-1]=0;
        }

        if(state==0 && alive==3){
            next[i][c-1]=1;
        }

    }

    for(j=0;j<c;j++){                               /* Taking care of first and last row */
        int alive,state;

        alive=neighbours(0,j,r,c);
        state=curr[0][j];
        next[0][j]=state;
        
        if(state==1 && (alive<2 || alive>3)){
            next[0][j]=0;
        }

        if(state==0 && alive==3){
            next[0][j]=1;
        }



        
        alive=neighbours(c-1,j,r,c);
        state=curr[c-1][j];
        next[c-1][j]=state;
        
        if(state==1 && (alive<2 || alive>3)){
            next[c-1][j]=0;
        }

        if(state==0 && alive==3){
            next[c-1][j]=1;
        }

    }

    int **temp = curr;                              /* Updating pointers to copy the data from one 2d matrix to another */
	curr = next;
	next = temp;

}

int main(int argc , char** argv)                /* taking arguments for matrix size and no. of steps  */
{

    int i,j,row,col,t_steps,steps;
    double start,stop;
    float x;

    row=atoi(argv[1]);                      /* initialising the no. of rows, column, and no. of steps from arguments */
    col=atoi(argv[2]);
    t_steps=atoi(argv[3]);

    curr=(int **)(malloc((row+1)*sizeof(int *)));               /* allocatting the memory of row using malloc  */
    next=(int **)(malloc((row+1)*sizeof(int *)));

    for(i=0;i<row;i++){
        curr[i]=(int *)(malloc((col+1)*sizeof(int)));
        next[i]=(int *)(malloc((col+1)*sizeof(int)));               /* allocatting the memory of column using malloc  */
        for(j=0;j<col;j++){
            /*x = rand()/((float)RAND_MAX + 1);
            if(x<0.25){
	            curr[i][j] = 0;
            }else{
	            curr[i][j] = 1;
            }*/
            curr[i][j]=rand()%2;                            /*  generating the random input  */
        }
    }

    start = omp_get_wtime();

    for(steps=0;steps<t_steps;steps++){
        change(row,col);
        //print(row,col);
    }    

    //print(row,col);    
    
    stop = omp_get_wtime();

    char file_name[100];

    strcpy(file_name, "Serial_Opt.txt");
    FILE* fp = fopen(file_name, "a+");
    
    fprintf(fp,"%0.10lf\n", (stop-start));
}
