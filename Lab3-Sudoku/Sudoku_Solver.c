#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
//#include <cell.h>





#define SIZE 9

typedef struct Cells{
    int possibility[9];
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











int  **solve_board(){

    while(threads_waiting < num_threads){
        while(outliers==0){
            threads_waiting ++;
            cv.wait();//condition variable
            threads_waiting ++;
        }

        temp = pop(outliers);
        index, value = MIN_POSSIBLE_VALUES(unsolved board);
        REDUCE(index, value, board);
        if valid_grid(board_prime){
            outliers.push(board_prime)
            explored.push(board_prime)
            cv.notify();
        }
        else{
            explored.push(board);
        }
    }
    return board_prime;
    }

void create_thread(num_threads, board){
    for(int i=num_threads;i<SIZE){
        num_threads(SOLVE(outliers, explored, board);
    }
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
 
