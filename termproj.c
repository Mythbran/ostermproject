/*
Gurbir Matharu
Matthew D'Angelo

SYST44288
Final Project
 */

#include <stdlib.h> /* required for rand */
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> /* required for sleep */
#include <errno.h>
#include "buffer.h"
#define true 1

/*global variables*/
pthread_mutex_t mutex;
sem_t empty, full;

//PROTOTYPES 
void *producer(void *param);
void *consumer(void *param);

int main(int argc, char *argv[]){
	int sleep_time, producer_arg, consumer_arg, i;
	/*error checking to make sure only 3 command line inputs are provided*/
	if (argc != 4){
    	printf("Please enter 3 arguments \nUsage is ./prog sleeptime producerThreads consumerThreads\n");
    	exit(1);
	}

	/* 1. Get command line arguments
	argv[1],argv[2],argv[3] */
	if((sleep_time = strtol(argv[1], NULL, 0)) ==0){
		fprintf(stderr, "Error converting Sleep Time Argument\n");
		exit(1);
	}
	if((producer_arg = strtol(argv[2], NULL, 0)) ==0){
		fprintf(stderr, "Error converting Producer Thread Argument\n");
		exit(1);
	}
	if((consumer_arg = strtol(argv[3], NULL, 0)) ==0){
		fprintf(stderr, "Error converting consumer Thread Argument\n");
		exit(1);
	}


	/* 2. Initialize buffer */
	srand(time(NULL));
  	if(pthread_mutex_init(&mutex, NULL)!=0){
  		perror("Error initializing mutex semaphore");
  		exit(2);
  	}
  	if((sem_init(&empty, 0, BUFFER_SIZE))==-1)
  		perror("Error initializing empty semaphore");
  	
	if((sem_init(&full, 0, 0))==-1)
  		perror("Error initializing empty semaphore");
  	
  	if(errno != 0){
  		printf("Error occured: %s\n", strerror(errno));
  		exit(2);
  	}
  	
	/* 3. Create producer thread(s) */
  	pthread_t producer_x[producer_arg];
	for(i = 0; i < producer_arg; i++)
		if((pthread_create(&producer_x[i], NULL, producer, NULL))!= 0)
			fprintf(stderr, "Producer Thread %d has failed", i);
		
	/* 4. Create consumer thread(s) */
		pthread_t consumer_x[consumer_arg];
  	for(i = 0; i < consumer_arg; i++)
		if((pthread_create(&consumer_x[i], NULL, consumer, NULL))!= 0)
			fprintf(stderr, "Consumer Thread %d has failed", i);
	

	/* 5. Sleep */
	sleep(sleep_time);
	/* 6. Exit */
	return 0;
	exit(0);
}

void *producer(void *param){

	buffer_item item;
	int random_sleep;

		while (true) {

			/* sleep for a random period of time */
			random_sleep = (rand() % 5 + 1); // sleep time wasn't given, using 1-10 so it isn't too long
			sleep(random_sleep);

			/* generate a random number */
			item = rand();

			//LOCKING CRITICAL SECTION 
			sem_wait(&empty);
			pthread_mutex_lock(&mutex);
				if (insert_item(item)== -1)
					printf("report error condition\n");
				else
					printf("producer produced %d\n",item);

			//UNLOCKING CRITICAL SECTION AND NOTIFYING CONSUMER
			pthread_mutex_unlock(&mutex);	
			sem_post(&full);

			//ERROR HANDLING 
			if(errno != 0){
				perror(strerror(errno));
				exit(3);
			}
		}
	}

void *consumer(void *param){

	buffer_item item;
	int random_sleep;

		while (true) {

			/* sleep for a random period of time */
			random_sleep = (rand() % 5 + 1); // sleep time wasn't given, using 1-10 so it isn't too long
			sleep(random_sleep);
			
			//LOCKING CRITICAL SECTION 
			sem_wait(&full);
			pthread_mutex_lock(&mutex);

			if (remove_item(&item)== 0)
				printf("consumer consumed %d\n",item);
			else
				printf("error");

			//UNLOCKING CRITICAL SECTION AND NOTIFYING PRODUCER
			pthread_mutex_unlock(&mutex);
			sem_post(&empty);

			//ERROR HANDLING 
			if(errno != 0){
				perror(strerror(errno));
				exit(3);
			}
		}
	}
