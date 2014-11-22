#include <stdio.h>

#define EOL 1 //the end of the line
#define ARG 2 
#define AMPERSAND 3
#define SEMICOLON 4
#define MAXARG 512 //the max nubmer of the parameters in the command line
#define MAXBUF 512 //THE MAX LENGTH OF THE COMMAND LINE
#define FOREGROUND 0
#define BACKGROUND 1

static char special[] = {' ','\t','*',';','\n','\0'};
/*************************************
 *functions
 *
 * ************************************/
inarg(char c);
userin(char* p);
procline();
runcommand(char** cline,int where);
gettok(char* output);

//program cache and point
static char inpbuf[MAXBUF], tokbuf[2*MAXBUF], *ptr = inpbuf, *tok = tokbuf;


inarg(char c){
	char *wrk;
	for(wrk=special;*wrk!='\0'; wrk++){
		if(c == *wrk){
			return(0);
		}
	}

	return(1);
}


//fucntion userin
int userin(char* p ){
	int c,count;

	ptr = inpbuf;
	tok = tokbuf;
	//show the imply
	printf("%s",p);
	for(count=0;;){
		if((c = getchar())== EOF)
			return(EOF);
		if(count<MAXBUF)
			inpbuf[count++] = c;
		if(c =='\n' && count<MAXBUF){
			inpbuf[count] = '\0';
			return(count);
		}

		//we need to reinput if the length of the line is too large 
		if (c=='\n'){
			printf("smallsh:input line too long\n");
			count = 0;
			printf("%s" ,p);
		}
	}
}

procline(){
	char* arg[MAXARG+1] ;
	int toktype;
	int narg;
	int type;

	for(narg=0;;){
		toktype=gettok(&arg[narg]);
		printf("%d\n",toktype );

		switch(toktype){
			case ARG:
				if(narg<MAXARG){
					narg++;
				}
				break;
			case EOL:
			case SEMICOLON:
			case AMPERSAND:

				type=(toktype==AMPERSAND)?BACKGROUND:FOREGROUND;
				if(narg!=0){

					arg[narg] = NULL;
					runcommand(arg,type);
				}
				if(toktype==EOL)
					return;
				narg = 0;
				break; 
		}
	}
}

runcommand(char ** cline,int where){
	int pid,exitstat,ret;

	if((pid = fork()) < 0){
		perror("fork fail");
		return(-1);
	}

	printf("%d\n",pid );
	if(!pid){
		printf("%s",*cline);
		char* clin[] = {"ls","-l",NULL};
		execvp("ls",clin);
		perror(*cline);
		printf("127\n");
		exit(127);
	}
	if(where == BACKGROUND){
		printf("[process id %d]\n",pid);
		return(0);
	}

	while((ret = wait(&exitstat))!=pid && ret!=-1);
	return (ret == -1 ?-1:exitstat);
	
}

gettok(char* output){
	int type;
	
	output = tok;

	//first delete the blank char
	for(; *ptr == ' ' || *ptr=='\t';ptr++);
	*tok++=*ptr;
	int t  = *ptr++;
	printf("%d\n",t );
	switch(t){
		case '\n':
			type = EOL;
			break;
		case '&':
			type = AMPERSAND;
			break;
		case ';':
			type = SEMICOLON;
			break;
		default:
			type=ARG;
			while(inarg(*ptr))
				*tok++=*ptr++;
	}
	*tok++ = '\0';
	printf("%s\n",output );
	return(type);
}
