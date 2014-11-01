#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>

int main(int argc, char *argv[]){
	struct hostent *h;
	//chech the argc
	if(argc != 2){
		//if there is no argc
		fprintf(stderr, "usageL getip address\n");
		//then exit
		exit(1);
	}

	//get the host information
	if ((h= gethostbyname(argv[1])) == NULL ){
		// if gethostbyname failed then put the wrong message
		herror("gethostbyname");
		//then exit
		exit(1);
	}

	//list the probgtram inf o
	printf("Host name: %s\n", h->h_name );
	printf("IP Address: %s\n",h->h_addr);

	return 0;
}