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
inarg(char c){
	char *wrk;
	for(wrk=special;*wrk!='\0'; wrk++){
		if(c == *wrk){
			return(0);
		}
	}

	return(1);
}

gettok(char* output){
	int type;
	printf("hello");	
	
	output	 = tok;
	//first delete the blank char
	for(; *ptr == ' ' || *ptr=='\t';ptr++);
	
	*tok++=*ptr;
	switch(*ptr++){
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
}


