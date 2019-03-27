/*
 * Banker's Algorithm for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>
#include "banker.h"

// Put any other macros or constants here using #define
// May be any values >= 0
#define NUM_CUSTOMERS 5
#define NUM_RESOURCES 3


// Put global environment variables here
// Available amount of each resource
int available[NUM_RESOURCES];

// Maximum demand of each customer
int maximum[NUM_CUSTOMERS][NUM_RESOURCES];

// Amount currently allocated to each customer
int allocation[NUM_CUSTOMERS][NUM_RESOURCES];

// Remaining need of each customer
int need[NUM_CUSTOMERS][NUM_RESOURCES];

pthread_mutex_t mlock;








void *customerMethod(void *custNum){
    //cast the customer number
    int customer = *(int*)custNum;
    bool acquiredResources = false;


    //the arrays of the resources for the specific customer
    int request [NUM_RESOURCES];
    
    while(1){
        for(int i = 0; i < NUM_RESOURCES; i++){
            //request a random number of resources from 0 to the maximum in the system
            //this will allow the needy state to become true sometimes
            request[i] = rand() % (maximum[customer][i] + 1); 
        }
        pthread_mutex_lock(&mlock);
        //try to get the resources
        acquiredResources = request_res(customer,request);
        pthread_mutex_unlock(&mlock);
        if(acquiredResources){
            sleep((int)rand() % 5 + 1);
            acquiredResources = false;
            pthread_mutex_lock(&mlock);
            release_res(customer,request); //release the resources used
            pthread_mutex_unlock(&mlock);
            //simulate the customer has finished its task.
            if(rand() % 2 == 0){
                printf("\nCustomer : %d is finished\n", customer);
                for(int i = 0; i < NUM_RESOURCES; i++){
                    need[customer][i] = 0;
                    maximum[customer][i] = 0;
                }
                printf("Maximum Needs After the Customer Finished\n");
                for(int i = 0; i < NUM_CUSTOMERS; i++){
                    for(int j = 0; j < NUM_RESOURCES; j++){
                        printf("%3d ",maximum[i][j]);
                    }
                    puts("");
                }
                sleep(2);
                break;
            }
        }
        sleep(1);
    }
    return 0;
}

bool isSafe(){

    //assign the work array to the current available resources
    int work[NUM_RESOURCES];
    for(int i = 0; i < NUM_RESOURCES; i++){
        work[i] = available[i];
    }
    //assign all customers a finish of false, in order to find a safe state
    bool finish [NUM_CUSTOMERS];
    for(int i = 0; i < NUM_CUSTOMERS; i++){
        finish[i] = false;
    }

    int count = 0;
    //used to check if the system could not find any customer that can execute with the resources currently
    int indexFinish = -1;
    int prevFinishIndex = -1;
    bool finishCustomer = true;

    //go through all the customers and see if the system is safe
    while (count < NUM_CUSTOMERS){
        prevFinishIndex = indexFinish; //assign the previous finish index to the last one
        //go through all the customers
        for(int i = 0; i < NUM_CUSTOMERS; i++){
            //if the customer is not done, check to see if it can be completed
            if(!finish[i]){
                for(int j = 0; j < NUM_RESOURCES; j++){
                    if (need[i][j] > work[j])
                        finishCustomer = false;
                }
                //if it can be completed, set the finish array to true, and the inxedFinish to the current index
                if(finishCustomer){
                    indexFinish = i;
                    for(int j = 0; j < NUM_RESOURCES; j++){
                        work[j] += allocation[i][j]; //give back the resources for work
                    }
                    finish[i] = true;
                    count++;
                    finishCustomer = true;
                    break; //exit loop and go through the list again
                }
            }
        }

        //see if the system has aquired a safe path for the customer execution
        for(int i = 0; i < NUM_CUSTOMERS; i++){
            if(!finish[i])
                break;
        }
        //see if there was no change in the finish array after going though each customer
        if(prevFinishIndex == indexFinish)
            return false;
    }
    return true;
}



bool request_res(int n_customer, int request[])
{
    printf("\nCustomer: %d requests resources\n", n_customer);
    for(int i=0;i<NUM_RESOURCES; i++){
        printf("%d ", request[i]);
    }
    puts(" ");

    printf("Available Before:\n");
    for(int i=0;i<NUM_RESOURCES; i++){
        printf("%d", available[i]);
    }

    puts(" ");
    for(int i=0;i<NUM_RESOURCES; i++){
        if(request[i] <= need[n_customer][i]){
            if(request[i] > available[i]){
                printf("Not Safe!\n\n");
                sleep(1);
                return false;
            }
            else{
                printf("safety check in progress");
                for(int k = 0; k < NUM_RESOURCES; k++){
                    allocation[n_customer][k] += request[k];
                    available[k] -= request[k];
                    need[n_customer][k] -= request[k];
                }
                if(isSafe()){
                    printf("It's Safe!\nResources Granted!\n");
                    printf("Updated Available Resources:\n");
                    for(int i = 0; i < NUM_RESOURCES; i++){
                        printf("%d ",available[i]);
                    }
                    puts("\n");
                    sleep(2);
                    return true;
                }
                else{
                    printf("Not Safe!\nResources Denied!\n");
                    for(int k = 0; k < NUM_RESOURCES; k++){
                        available[k] += request[k]; //add to the available resources
                        need[n_customer][k] += request[k]; //add to the customers need array
                        allocation[n_customer][k] -= request[k]; //reduce the allocation for the customer
                    }
                    return false;
                }
            }
        } else{
            printf("Customer: %d Needs\n",n_customer);
            sleep(1);
            return false;
        }

    }
 
    return true;
}



//Release resources, returns true if successful
bool release_res(int n_customer, int release[])
{
    printf("\nCustomer: %d Releasing Resources\n", n_customer);
    for(int i = 0; i < NUM_RESOURCES; i++){
        printf("%d ",release[i]);
        available[i] += release[i]; //add to the available resources
        need[n_customer][i] += release[i]; //add to the customers need array
        allocation[n_customer][i] -= release[i]; //reduce the allocation for the specific customer
    }

    puts("");
    printf("Updataed Available Resources:\n");
    for(int i = 0; i < NUM_RESOURCES; i++){
        printf("%d ",available[i]);
    }
    puts("");
    sleep(2);
    return true;
}


int main(int argc, char *argv[])
{
    // ==================== YOUR CODE HERE ==================== //

    // Read in arguments from CLI, NUM_RESOURCES is the number of arguments   
    pthread_t threads[NUM_CUSTOMERS];
    pthread_mutex_init(&mlock, NULL);
    for (int i =0; i < NUM_RESOURCES; i++) {
        //Specifies the max INITIAL availale resources. MAX cannot exceed this
        available[i] = atoi(argv[i+1]);
        //go through the customers and randomly state how many resources they need at maximum
        for(int j=0; j<NUM_CUSTOMERS; j++) {
            maximum[j][i] = rand() % (available[i] + 1);
            need[j][i] = maximum[j][i];
            allocation[j][i] = 0;
        }        
    }

    // Allocate the available resources


   //print out the needs of all customers
    printf("Maximum Needs\n");
    for(int i = 0; i < NUM_CUSTOMERS; i++){
        for(int j = 0; j < NUM_RESOURCES; j++){
            printf("%3d ",maximum[i][j]);
        }
        puts("");
    }
    srand(time(NULL));
    //make all the customers
    for(int i = 0; i < NUM_CUSTOMERS; i++){
        int *c_num = malloc(sizeof(*c_num));
        //make an integer pointer to be used to send into the customer thread
        if(c_num ==NULL){
            printf("couldn't make customer number");
            exit(1);
        }
        *c_num = i;
        //create the customer thread
        pthread_create(&threads[i],NULL,&customerMethod, c_num);
    }
    
    //join all the threads (will never happen)
    for(int i = 0; i < NUM_CUSTOMERS; i++){
        pthread_join(threads[i],0);
    }
    printf("DONE\n");
    pthread_mutex_destroy(&mlock);
    
    return EXIT_SUCCESS;
}
