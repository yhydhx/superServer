#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

//The  keyword in the shared memory
#define SHMKEY1 (key_t)0x10
#define SHMKEY2 (key_t)0x15
//The keyword of the signal
#define SEMKEY (key_t)0x20

// The size of the cache
#define	SIZ 5*BUFSIZ

struct  databuf{
	int d_nread;
	char d_buf[SIZ];
};

#define IFLAGS (IPC_CREAT | IPC_EXCL)
#define ERR ((struct databuf*) -1)

static int shmid1, shmid2, semid;

fatal(char *mes){
	perror(mes);
	exit(1);
}

getseg(struct databuf** p1, struct databuf** p2){
	//create share memory
	if ((shmid1 = shmget(SHMKEY1, sizeof(struct databuf), 0600|IFLAGS)) < 0){
		fatal("shmget");
	}

	if ((shmid2 = shmget(SHMKEY2, sizeof(struct databuf), 0600|IFLAGS)) < 0){
		fatal("shmget");
	}

	//establish the connection between the share memory
	if ((*p1 = (struct databuf*)(shmat(shmid1,0,0))) == ERR){
		fatal("shmat");
	}

	if((*p2 = (struct databuf*)(shmat(shmid1,0,0))) == ERR){
		fatal("shmat");
	}
}

int getsem(){
	//establish the signal object
	if((semid = semget(SEMKEY, 2 , 0600|IFLAGS))< 0){
		fatal("semget");
	}

	//initial the segmal object
	if(semctl(semid, 0, SETVAL,0) <0){
		fatal("semget");
	}

	if(semctl(semid, 1, SETVAL,0) < 0){
		fatal("semctl");
	}

	return(semid);
}

fremove(){
	if(shmctl(shmid1, IPC_RMID, NULL) < 0){
		fatal("shmctl");
	}

	if(shmctl(shmid2, IPC_RMID, NULL) < 0){
		fatal("shmctl");
	}

	if(shmctl(semid, IPC_RMID, NULL) < 0){
		fatal("semctl");
	}
}

/********************************************
 *  reader
 *
 **********************************************/

 struct sembuf p1 = {0, -1 , 0}, p2 = {1, -1, 0 }, v1 = {0,1,0}, v2 = {1,1,0};

 reader(int semid, struct databuf *buf1, struct databuf *buf2){
 	for(;;){
 		//Read the buf1
 		buf1->d_nread = read(0, buf1->d_buf, SIZ);

 		//syn
 		semop(semid, &v1, 1);
 		semop(semid, &p2, 1);

 		//prevent sleep
 		if(buf1->d_nread <= 0){
 			return;
 		}

 		buf2->d_nread(0, buf2->d_buf, SIZ);

 		semop(semid, &v2, 1);
 		semop(semid, &p1, 1);

 		if(buf2->d_nread <= 0){
 			return;
 		}
 	}
 }


/********************************************
 *  reader
 *
 **********************************************/

 extern struct sembuf p1,p2;
 extern struct sembuf v1, v2;

 writer(int semid, struct databuf buf1, struct databuf buf2){
 	for(;;){
 		semop(semid, &p1, 1);
 		if(buf1->d_nread <= 0){
 			return;
 		}

 		wirte(1, buf1->d_buf, buf1->d_nread);

 		semop(semid, &v1, 1);
 		semop(semid, &v2, 1);

 		if(buf2->d_nread <=0){
 			return;
 		}

 		write(1, buf2->d_buf, buf2 -> d_nread);
 		semop(semid, &v2, 1);
 	}
 }

