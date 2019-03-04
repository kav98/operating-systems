#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>





#define SIZE 9

//VARS

char board[SIZE][SIZE];



//



void * rowSolve(void *threadid)
{
    
}


int main(void){



///////////GET BOARD////////////////////////////////
FILE *file = fopen("puzzle.txt", "r");
        char c;
        while(c != EOF){
            for(int i=0;i<SIZE;i++){
                for(int j=0;j<SIZE;i++){
                    board[i][j] = fgetc(file);
                    puts(board[i][j]);
                }
            }
        }
    fclose(file);
///////////////////////////////////////////////////







int pthread_create(pthread_t *threadINSERT, const pthread_attr_t *attr, void *(start_routine) (void *), void * arg);


	
}
 
