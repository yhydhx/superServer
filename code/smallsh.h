#include <stdio.h>

#define EOL 1 //the end of the line
#define ARG 2 
#define AMPERSAND 3
#define SEMICOLON 4
#define MAXARG 512 //the max nubmer of the parameters in the command line
#define MAXBUF 512 //THE MAX LENGTH OF THE COMMAND LINE
#define FOREGROUND 0
#define BACKGROUND 1

gettok(char* output){
	int type;
	
	outptr = tok;
	//first delete the blank char
	for(; *ptr == '' || *ptr=='\t';ptr++);
	
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
	return(type);
	}
}
