/*---------------------------------------------
Serial implementation of Naive Approach
Author:  201501452 - Dhruv Patel
	 201501408 - Raj Jakasaniya
---------------------------------------------*/

#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int **curr;
int **next;

int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};			/* for traversing neighbours  */
int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};

void print(int row,int col)				/* function for printing output martix which take no. of row and no. of column as parameter */
{
	int i, j;
	for (i = 0; i < row; ++i)
	{
		for (j = 0; j < col; ++j)
		{
			printf("%d ",curr[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int neighbours(int x,int y,int row,int col){		/* this function gives the no. of neighbours alive cell (x,y)  */
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

void change(int rw,int cl){				/*  this function change the state of cell according to the rules */
    int x,y;
    for(x=0;x<rw;x++){
        for(y=0;y<cl;y++){
            
            int live = neighbours(x,y,rw,cl);
            int state = curr[x][y];
            
            next[x][y] = state;
            if(state==1 && (live<2 || live>3)){		/*  if the cell is live and it is underpopulated or overpopulated then it dies  */
                next[x][y]=0;
            }
            
            if(state==0 && live==3){			/*  if cell is dead and the no. of neighbours alive is 3 then cell becomes alive */ 
                next[x][y]=1;
            } 
        }
    }

    for(x=0;x<rw;x++){					/* coping new status matrix to curr matrix  */
        for(y=0;y<cl;y++){
            curr[x][y]=next[x][y];
        }
    }
}

int main(int argc , char** argv)			/* taking arguments for matrix size and no. of steps  */
{

    int i,j,row,col,t_steps,steps;			/*  initialising the variable  */
    double start,stop;
    float x;

    row=atoi(argv[1]);					/* initialising the no. of rows, column, and no. of steps from arguments */
    col=atoi(argv[2]);
    t_steps=atoi(argv[3]);

    curr=(int **)(malloc(row*sizeof(int *)));		/* allocatting the memory of row using malloc  */
    next=(int **)(malloc(row*sizeof(int *)));

    for(i=0;i<row;i++){
        curr[i]=(int *)(malloc(col*sizeof(int)));		/* allocatting the memory of column using malloc  */
        next[i]=(int *)(malloc(col*sizeof(int)));
        for(j=0;j<col;j++){
            x = rand()/((float)RAND_MAX + 1);			/*  generating the random input  */
            if(x<0.5){
	            curr[i][j] = 0;
            }else{
	            curr[i][j] = 1;
            }    
        }
    }

    start = omp_get_wtime();				/* calculating the time  */

    for(steps=0;steps<t_steps;steps++){
        change(row,col);
    }    

    //print(row,col);    
    
    stop = omp_get_wtime();

    char file_name[100];

    strcpy(file_name, "Serial.txt");			/* opening a file  */
    FILE* fp = fopen(file_name, "a+");
    

    fprintf(fp,"%0.10lf\n", (stop-start));			/* writing time in file  */
}
