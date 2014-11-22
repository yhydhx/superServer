#include <stdio.h>
#include <signal.h>

#define TIMEOUT 5
#define MAXTRIES 5
#define LINESIZE 100
#define BELL '\007'
#define TRUE 1
#define FALSE 0

//CHECK WHETHER THE TIME IS OUT
static int time_out;

static char inputline[LINESIZE];
char* quickreply(char* prompt);

main(){
	printf("%s\n",quickreply("Input"));
}

char* quickreply(char* prompt){
	int (*was)(),catch(),ntries;
	char* answer;

	/*catch the siganl and store it*/
	was = signal(SIGALRM,catch);

	for(ntries = 0; ntries<MAXTRIES ; ntries++){
		time_out = FALSE;
		printf("\n%s>",prompt);

		//set the time out
		alarm(TIMEOUT);

		//get the input
		answer = gets(inputline);
	}
}