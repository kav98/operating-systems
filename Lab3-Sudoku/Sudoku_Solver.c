#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>





#define SIZE 9

//VARS

char board[SIZE][SIZE];



//




int **create_board(){
    int **board = (int **)malloc(SIZE * sizeof(int));
    
    

    
}









int main(void){

///////////GET BOARD////////////////////////////////
FILE *file = fopen("puzzle.txt", "r");
        char c;
        while(c != EOF){
            for(int i=0;i<SIZE;i++){
                for(int j=0;j<SIZE;j++){
                    board[i][j] = fgetc(file);
                }
            }
        }
    fclose(file);
///////////////////////////////////////////////////







int pthread_create(pthread_t *threadINSERT, const pthread_attr_t *attr, void *(start_routine) (void *), void * arg);


	
}
 
