#include <stdio.h>

int main(void){
	FILE *pipein_fp, *pipeout_fp;
	char readbuf[80];
	// estabilish a pipe to popen
	if((pipein_fp = popen("ls","r")) == NULL){
		perror("popen");
		exit(1);
	}

	//establish a pipe to sort
	if((pipeout_fp = popen("sort", "w")) == NULL){
		perror("popen");
		exit(1);
	}

	//loop
	while(fgets(readbuf,80,pipein_fp))
		fputs(readbuf, pipeout_fp);

	//close opened pipe
	pclose(pipein_fp);
	pclose(pipeout_fp);

	return(0);
}