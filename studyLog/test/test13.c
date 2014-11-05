#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define  UNIXEPOCH 2208988800UL
void main(){
	time_t now;
	char pblgtime[20];
	now =  time(NULL);
	strftime(pblgtime,20,"%Y-%m-%d %X",localtime(&now));
	printf(" %s\n",pblgtime);
}

