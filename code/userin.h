#include "smallsh.h"

//program cache and point

static char inpbuf[MAXBUF], tokbuf[2*MAXBUF], *ptr = inpbuf, *tok = tokbuf;

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
