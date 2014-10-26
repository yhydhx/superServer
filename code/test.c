#include <stdio.h>

extern char** environ;

main(){
	char *argv[] = {"showenv",NULL}, *envp[] = {"foo=var", "var=foo",NULL};
	execve("./showenv",argv,envp);
	perror("exeve failed");
	return;
}


