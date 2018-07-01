#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int **curr;
int **next;

int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};

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

void change(int rw,int cl){
    int x,y;
    for(x=0;x<rw;x++){
        for(y=0;y<cl;y++){
            
            int live = neighbours(x,y,rw,cl);
            int state = curr[x][y];
            
            next[x][y] = state;
            if(state==1 && (live<2 || live>3)){
                next[x][y]=0;
            }
            
            if(state==0 && live==3){
                next[x][y]=1;
            } 
        }
    }

    for(x=0;x<rw;x++){
        for(y=0;y<cl;y++){
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

    curr=(int **)(malloc(row*sizeof(int *)));
    next=(int **)(malloc(row*sizeof(int *)));

    for(i=0;i<row;i++){
        curr[i]=(int *)(malloc(col*sizeof(int)));
        next[i]=(int *)(malloc(col*sizeof(int)));
        for(j=0;j<col;j++){
            x = rand()/((float)RAND_MAX + 1);
            if(x<0.5){
	            curr[i][j] = 0;
            }else{
	            curr[i][j] = 1;
            }    
        }
    }

    start = omp_get_wtime();

    for(steps=0;steps<t_steps;steps++){
        change(row,col);
    }    

    //print(row,col);    
    
    stop = omp_get_wtime();

    char file_name[100];

    strcpy(file_name, "Serial.txt");
    FILE* fp = fopen(file_name, "a+");
    

    fprintf(fp,"%0.10lf\n", (stop-start));
}
