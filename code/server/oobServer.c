#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <fcntl.h>

                                                                                                                                                   
	//fix the bug: old_sig_urg_handle didn't define
                  
	//check the error
	if ((sockfd = socket (AF_INET, SOCK_STREAM, 0 )) == -1){
		perror("socket");
		exit(1);
	}

	my_addr.sin_port = htons(MYPORT);
	my_addr.sin_addr.s_addr = INADDR_ANY;

	bzero(&(my_addr.sin_zero), 8);
	if (bind(sockfd, (struct sockaddr *) & my_addr, sizeof(struct sockaddr)) == -1){
		perror("bind");
		exit(1);
	}

	//check the error
	if(listen(sockfd, BACKLOG) == -1){
		perror("listen");
		exit(1);
	}

	old_sig_urg_handle = signal(SIGURG, sig_urg);
	fcntl (sockfd, F_SETOWN, getpid());

	while(1){
		sin_size = sizeof(struct sockaddr_in);
		//check the error
		if((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1){
			perror("accept");
			continue;
		}

		printf("server: got connection from %s\n", inet_ntoa(their_addr.sin_addr));

		if(!fork()){
			while(1){
				if ((n = recv(new_fd, buff, sizeof(buff) -1)) == 0){
					printf("received EOF\n");
					break;
				}

				buff[n] = 0;
				printf("Recv %d bytes: %s\n", n, buff);
			}
			close(new_fd);
		}
	}

	while(waitpid(-1,NULL, WNOHANG) > 0);
	signal(SIGURG, old_sig_urg_handle);
}

void sig_urg(int signo){
	int n, new_fd;
	char buff[100];

	printf("SIGURG received \n");
	n = recv(new_fd, buff, sizeof(buff)-1, MSG_OOB);
	buff[n] = 0;
	printf("recv %d OOB byte: %s\n", n, buff);
}                                                                                                                                                 