#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int **curr;
int **next;
int **prefix;


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

void prefix_sum(int row,int col)
{
    int x,y;
    for(x=2;x<row;x++)
    {
        for(y=2;y<col;y++)
        {
            prefix[x][y] = curr[x][y] - prefix[x-1][y-1] + prefix[x-1][y] + prefix[x][y-1];
        }
    }
}

void change(int row,int col)
{
    prefix_sum(row,col);
    int x,y;
    for(x=2;x<row-1;x++)
    {
        for(y=2;y<col-1;y++)
        {
            
            int live = prefix[x+1][y+1] - prefix[x-2][y+1] - prefix[x+1][y-2] + prefix[x-2][y-2] - curr[x][y];
            int state = curr[x][y];
            
            next[x][y] = state;

            if(state==1 && (live<2 || live>3))
            {
                next[x][y]=0;
            }
            
            if(state==0 && live==3){
                next[x][y]=1;
            } 
        }
    }

    for(x=2;x<row-1;x++){
        for(y=2;y<col-1;y++){
            curr[x][y]=next[x][y];
        }
    }
}

int main(int argc , char** argv)
{

    int i,j,row,col,t_steps,steps;
    double start,stop;
    float x;

    row=atoi(argv[1]);
    col=atoi(argv[2]);
    t_steps=atoi(argv[3]);

    curr=(int **)(malloc((row+4)*sizeof(int *)));
    next=(int **)(malloc((row+4)*sizeof(int *)));
    prefix=(int **)(malloc((row+4)*sizeof(int *)));
    for(i=0;i<(row+4);i++)
    {
        curr[i]=(int *)(malloc((col+4)*sizeof(int)));
        next[i]=(int *)(malloc((col+4)*sizeof(int)));
        prefix[i]=(int *)(malloc((col+4)*sizeof(int)));
        for(j=0;j<(col+4);j++)
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
    

    start = omp_get_wtime();

    for(steps=0;steps<t_steps;steps++)
    {
        //print(row+4,col+4);
        change(row+4,col+4);
        //print(row+4,col+4);
    } 

    //print(row+4,col+4);    
    
    stop = omp_get_wtime();

    char file_name[100];

    strcpy(file_name, "Serial_Prefix.txt");
    FILE* fp = fopen(file_name, "a+");
    
    fprintf(fp,"%0.10lf\n", (stop-start));
}
