/*named pipe server*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <linux/stat.h>

#define FIFO_FILE "sampleFIFO"

int main(void){
	FILE *fp;
	char readbuf[80];

	/*create the FIFO if it does not exit*/
	umask(0);

	//create named pipe
	mknod(FIFO_FILE,S_IFIFO|06666, 0);

	while(1){
		//open named pipe
		fp = fopen(FIFO_FILE , "r");

		//get data from named pipe
		fgets(readbuf, 80, fp);
		printf("Receive string: %s\n", readbuf);

		//close named pipe
		fclose(fp);
	}
	return(0);
}

