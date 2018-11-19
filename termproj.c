#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "buffer.h"

/*THE BUFFER */
buffer_item buffer[SIZE];

//PROTOTYPES 
int insert_item(buffer_item item);
int remove_item(buffer_item *item);
void *producer(void *param);
void *consumer(void *param);

int main(int argc, char *argv[]){
	int sleep_time, producer_arg, consumer_arg, i;
	/*error checking to make sure only 3 command line inputs are provided*/
	if (argc != 4){
    	printf("3 inputs needed, program will exit, try again");
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
  	sem_init(&empty, 0, BUFFER_SIZE); 
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
	exit(1);
}


int insert_item(buffer_item item){
	//INSERT ITEM INTO THE BUFFER 
	//return 0 if succesfull, 
	//return -1 if unsuccessful 
}

int remove_item(buffer_item *item){
	//remove an object from buffer 
	//placing it into item 
	//return 0 if successful 
	//return -1 if unsuccessful 
}

void *producer(void *param){
	buffer_item item; 

	while(1){
		//sleep for a random period of time 
		//sleep(...);
		//generate a random number
		//item = rand():
		//if(inser item(item))
			//print error
		//else
			//print item 
			//printf("producer produced %d\n", item);
	}
}

void *consumer(void *param){
	//buffer_item item; 

	while(1){
		//sleep for random period of time 
		//sleep(...);
		//if (remove item(&item))
			//fprintf("report error condition"):
		//else
			//printf("consumer consumer %d\n", item);


	}

}
