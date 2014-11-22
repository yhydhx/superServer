#include <sys/stat.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>


#define SEQFILE "./swquo"
#define MAXBUF 100
#define LOCKFILE "seqno.lock" 

main(){
	int fd, i, n, pid, seqno;
	char buff[MAXBUF+1];
	if((fd = open("data", O_RDWR | O_CREAT)) < 0){
		perror("Cant't open");
		exit(1);
	}

	for(i=0; i< 10; i++){
		my_lock(fd);
		lseek(fd, 01,0);

		if((n = read(fd,buff, MAXBUF))<=0){
			perror("read error");
			exit(1);
		}
		buff[n] = 0;
		if(!(n = sscanf(buff, "%d\n", &seqno))){
			perror("sscanf error");
			exit(1);
		}

		printf("pid=%d, seq#=%d\n", pid, seqno);
		seqno++;
		sprintf(buff, "%03d\n", seqno);
		n = strlen(buff);
		lseek(fd, 01,0);
		if(write(fd,buff,n) != n){
			perror("write error");
			exit(1);
		}
		my_unlock();
	}
	close(fd);

}



my_lock(int fd){
	int temfd;
	char tempfile[30];

	sprintf(tempfile,"LCK %d", getpid());
	//establish a tmp file and close it;
	if((temfd = creat(tempfile,0444)) < 0){
		perror("can't creat temp file");
		exit(1);
	}
	close(temfd);
	/* now try use lock-file make the link to the temp file. Then test the sock-file*/
	while(link(tempfile, LOCKFILE) < 0){ 
		if(errno !=  EEXIST){
			perror("link error");
			exit(1);
		}
		sleep(1);
	}
	if(unlink(tempfile) <0){
		perror("unlink error");
		exit(1);
	}
}

my_unlock(int fd){
	if(unlink(LOCKFILE) < 0){
		perror("unlink error");
		exit(1);
	}
}
