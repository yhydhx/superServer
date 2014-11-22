#include <string.h>
#include <stdio.h>

main(){
	char a[9999] = "hello world";
	char b[11]= " ";
	char*  result = NULL;

	result = strtok(a,b);
	printf("hellowr \n%s\n",result);
	result = strtok(NULL,b);
	printf("hellowr \n%s\n",result);
}
