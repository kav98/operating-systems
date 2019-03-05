#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>





#define SIZE 9

//VARS

//char board[SIZE][SIZE];



//




int **create_board(){
    //allocate the space for the rows
    int **board = (int **)malloc(SIZE * sizeof(int));
    
    //allocate space for the coloums
    for(int i = 0; i<SIZE;i++){
        board[i] = (int *)malloc(SIZE*sizeof(int));
    }
    
}

void free_board(int **board){
    for(int i = 0; i< SIZE; i++){
        free(board[i]);
    }
}


int  **solve_board(){

    while(threads_waiting < num_threads){
        while(outliers==0){
            threads_waiting ++;
            cv.wait();
            threads_waiting ++;
        }

        temp = outliers.pop();
        index, value = MIN_POSSIBLE_VALUES(unsolved board)
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
 
