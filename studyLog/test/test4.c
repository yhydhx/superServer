#include <stdio.h>
#include <setjmp.h>
#include <signal.h>

jmp_buf position;

main(){
	int goback();

	//save the current positon of  the environment
	setjmp(position);
	signal(SIGINT, goback);
	domenu();
}

goback(){
	fprintf(stderr, "\nInterrupted\n");
	//back to the break point
	longjmp(position,1);
}