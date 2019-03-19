#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
//#include <cell.h>





#define SIZE 9

typedef struct Cells{
    int possibility[SIZE];
    short value;

}Cell;

//VARS

pthread_t tid[4];
int count;
pthread_mutex_t lock;


Cell board[SIZE][SIZE];




//


int pop(){
    int data;

}





int main(void){

///////////GET BOARD////////////////////////////////
FILE *file = fopen("puzzle.txt", "r");
        char c;
        char board[SIZE][SIZE];
        while(c != EOF){
            for(int i=0;i<SIZE;i++){
                for(int j=0;j<SIZE;j++){
                    board[i][j] = fgetc(file);
                }
            }
        }
    fclose(file);
///////////////////////////////////////////////////










	
}
 
