#include "share_ex.h"

main(){
	int semid, pid;
	struct datebuf *buf1, *buf2;

	//init the sem object
	semid = getsem();

	//create and connect the shared memory
	getseg(&buf1, &buf2);

	switch(pid = fork()){
		case -1:
			fatal("fork");
		case 0:
			writer(semid, buf1, buf2);
			fremove();
			break;
		default:
			reader(semid,buf1,buf2);
			break;
	}

	exit(0);
}