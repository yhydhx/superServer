#include <stdio.h>
#include <signal.h>

#define TRUE 1
#define FALSE 0
#define BELLS "\007\007\007"

int alarm_flag = FALSE;

//SIGALRM  
setflag(){
	alarm_flag = TRUE;
}

main(int argc, char*argv[]){
	int nsecs;
	int i ;

	if (argc<2){
		fprintf(stderr, "Usage:tml #minutes message\n");
		exit(1);
	}

	if((nsecs = atoi(argv[1]) * 60) <= 0){
		fprintf(stderr, "Invalid time\n");
		exit(2);
	}

	//set relative action of sigalrm
	signal(SIGALRM, setflag);
	//set time 
	alarm(nsecs);
	//use pause wait the wait signal
	pause();

	if(alarm_flag){
		printf(BELLS);
		for(i = 2; i < argc; i++){
			printf("%s\n", argv[i] );
		}
	}
	exit(0);

}