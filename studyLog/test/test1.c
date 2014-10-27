/*************************************
 * 20141027 
 * jupiter dai
 * test catch signal
 **************************************/

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

int catch(int sig);

int main(void){
	signal(SIGINT,catch); //handler there is the another function
	printf("xixi\n");
	sleep(10);
	printf("end");
	return;
}

int catch(int sig){
	printf("Catch succedd!\n");
	return 1;
}
