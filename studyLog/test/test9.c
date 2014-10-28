/*named pipe client*/

#include <stdio.h>
#include <stdlib.h>

#define FIFO_FILE   "sampleFIFO"

int main(int argc, char* argv[]){
	FILE * fp;

	if (argc != 2){
		printf("USAGE: fifoclient [string] \n");
		exit(1);
	}

	//open named pipe
	if((fp= fopen(FIFO_FILE,"w")) == NULL){
		perror("fopen");
		exit(1);
	}

	//write data to named pipe
	fputs(argv[1] , fp);
	//close named pipe
	fclose(fp);
	return(0);
}