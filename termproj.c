#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <buffer.h>

//HEADER
typedef int buffer_item; 
#define BUFFER_SIZE 5; 

/*THE BUFFER */
buffer_item buffer[BUFFER_SIZE];

int insert item (buffer_item item){
	//INSERT ITEM INTO THE BUFFER 
	//return 0 if succesfull, 
	//return -1 if unsuccessful 
}

int remove item(buffer_item *item){
	//remove an object from buffer 
	//placing it into item 
	//return 0 if successful 
	//return -1 if unsuccessful 
}

int main(int argc, char *argv[]){
	//GET COMMAND LINE ARGUMENTS
	//initialize buffer 
	//create producer thread(s)
	//create consumer thread(s)
	//sleep 
	//EXIT
}

void *producer(void *param){
	buffer_item item; 

	while(true){
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

	while(true){
		//sleep for random period of time 
		//sleep(...);
		//if (remove item(&item))
			//fprintf("report error condition"):
		//else
			//printf("consumer consumer %d\n", item);


	}

}