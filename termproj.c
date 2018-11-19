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
#include "buffer.h"

/*global variables*/
pthread_mutex_t mutex;
sem_t empty, full;



#define true 1

//PROTOTYPES 
void *producer(void *param);
void *consumer(void *param);

int main(int argc, char *argv[]){
	int sleep_time, producer_arg, consumer_arg, i;
	/*error checking to make sure only 3 command line inputs are provided*/
	if (argc != 4){
    	printf("3 inputs needed, program will exit, try again\n");
    	exit(1);
	}

	/* 1. Get command line arguments
	argv[1],argv[2],argv[3] */
	sleep_time = strtol(argv[1], NULL, 0);
	producer_arg = strtol(argv[2], NULL, 0);
	consumer_arg = strtol(argv[3], NULL, 0);
	/* 2. Initialize buffer */
	srand(time(NULL));
  	pthread_mutex_init(&mutex, NULL);
  	if((sem_init(&empty, 0, BUFFER_SIZE))==-1)
  		fprintf(stderr, "An error has occured"); 
	sem_init(&full, 0, 0);

	/* 3. Create producer thread(s) */
  	pthread_t producer_x[producer_arg];
	for(i = 0; i < producer_arg; i++)
		pthread_create(&producer_x[i], NULL, producer, NULL);
	/* 4. Create consumer thread(s) */
		pthread_t consumer_x[consumer_arg];
  	for(i = 0; i < consumer_arg; i++)
		pthread_create(&consumer_x[i], NULL, consumer, NULL);
	

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
			sem_wait(&empty);
			pthread_mutex_lock(&mutex);
				if (insert_item(item)== -1)
					printf("report error condition\n");
				else
					printf("producer produced %d\n",item);
			pthread_mutex_unlock(&mutex);	
			sem_post(&full);
		}
	}

void *consumer(void *param){
	buffer_item item;
	int random_sleep;
		while (true) {
			/* sleep for a random period of time */
			random_sleep = (rand() % 5 + 1); // sleep time wasn't given, using 1-10 so it isn't too long
			sleep(random_sleep);
			sem_wait(&full);
			pthread_mutex_lock(&mutex);
			if (remove_item(&item)== 0)
				printf("consumer consumed %d\n",item);
			else
				printf("error");
			pthread_mutex_unlock(&mutex);
			sem_post(&empty);
		}
	}
