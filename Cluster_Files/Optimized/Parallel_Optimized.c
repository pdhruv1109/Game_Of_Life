/*---------------------------------------------
Parallel implementation of Optimised Approach
Author:  201501452 - Dhruv Patel
	 201501408 - Raj Jakasaniya

Detail comment is in serial implementation here we have provided comment for parallel part only
---------------------------------------------*/


#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int **curr;
int **next;

int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};

int neighbours(int x,int y,int row,int col){
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

void print(int row,int col)
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

void change(int r,int c){
    int i,j,k;
    #pragma omp parallel for private(i, j)              /*  parallelizing the outer for loop (row wise )  */
    for(i=1;i<r-1;i++){
        int alive,state,c1=0,c2=0,c3=0;
        j=1;

        c1=curr[i][j - 1] + curr[i - 1][j - 1] + curr[i + 1][j - 1]; 
        c2=curr[i - 1][j] + curr[i + 1][j];
        c3=curr[i][j + 1] + curr[i - 1][j + 1] + curr[i + 1][j + 1];

        for(j=1;j<c-1;j++){
            alive=c1+c2+c3;

            c2=c2+curr[i][j];
            c3=c3-curr[i][j+1];
            
        
            c1=c2;
            c2=c3;
            c3=curr[i - 1][j + 2] + curr[i][j + 2] + curr[i + 1][j + 2];
    
            state=curr[i][j];
            next[i][j]=state;

            if(state==1 && (alive<2 || alive>3)){
                next[i][j]=0;
            }

            if(state==0 && alive==3){
                next[i][j]=1;
            }
        }
    }

    for(i=0;i<r;i++){
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

    for(j=0;j<c;j++){
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

    int **temp = curr;
	curr = next;
	next = temp;

}

int main(int argc , char** argv)
{

    int i,j,row,col,t_steps,steps;
    double start,stop;
    float x;

    row=atoi(argv[1]);
    col=atoi(argv[2]);
    t_steps=atoi(argv[3]);
    omp_set_num_threads(atoi(argv[4]));

    curr=(int **)(malloc((row+1)*sizeof(int *)));
    next=(int **)(malloc((row+1)*sizeof(int *)));

    for(i=0;i<row;i++){
        curr[i]=(int *)(malloc((col+1)*sizeof(int)));
        next[i]=(int *)(malloc((col+1)*sizeof(int)));
        for(j=0;j<col;j++){
            /*x = rand()/((float)RAND_MAX + 1);
            if(x<0.25){
	            curr[i][j] = 0;
            }else{
	            curr[i][j] = 1;
            }*/
            curr[i][j]=rand()%2;   
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

    strcpy(file_name, "Parallel_Opt_cores_");           /* opening and writing time in file  */
	strcat(file_name, argv[4]);
	strcat(file_name, ".txt");
    FILE* fp = fopen(file_name, "a+");
    
    fprintf(fp,"%0.10lf\n", (stop-start));
}
