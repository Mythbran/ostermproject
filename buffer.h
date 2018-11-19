/*
Gurbir Matharu
Matthew D'Angelo

SYST44288
Final Project
 */

typedef int buffer_item; 
#define BUFFER_SIZE 5
int in = 0;
int out = 0;
int num = 0;

buffer_item buffer[BUFFER_SIZE];

int insert_item(buffer_item item){
	//INSERT ITEM INTO THE BUFFER 
	//return 0 if succesfull, 
	//return -1 if unsuccessful 
	//printf("ITem buffer %d\n", item);
	if(((in +1 )%BUFFER_SIZE) == out){
		//BUFFER IS FULL 
		return -1;
	}
	buffer[in] = item;
	//printf("%d\n", buffer[in]);
	in = (in+1)%BUFFER_SIZE;
	return 0;
}

int remove_item(buffer_item *item){
	//remove an object from buffer 
	//placing it into item 
	//return 0 if successful 
	//return -1 if unsuccessful 
	//printf("in= %d out = %d \n", in ,out);
	if (in == out){
		return -1;
	}

	//printf("item %d\n", buffer[out]);

	*item = buffer[out];
	out = (out+1) %BUFFER_SIZE;
	return 0; 

}