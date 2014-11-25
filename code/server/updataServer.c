/************************************************
 *@author jupiter dai 			           		*
 *this server is for neibour box's  update transfering         *
 ************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>

//set the port need to listen 
#define MYPORT 4001

// SET THE NUMBER WE  CAN ACCPT IN A TIME
#define BACKLOG 10
#define MAXDATASIZE 100

main(){
	// listen on  sock_fd receive on new_fd
	int sock_fd, new_fd,numbytes;
	//my info about my address
	struct sockaddr_in my_addr;
	//connector's info
	struct sockaddr_in their_addr;
	char buf[MAXDATASIZE];
	
	memset(&their_addr, 0, sizeof(their_addr));
	

	socklen_t sin_size;
	//check the bug
	if((sock_fd = socket(AF_INET, SOCK_STREAM,0)) == -1){
		//print the error message and exit
		perror("socket");
		exit(1);
	}
	
	////the sequence of the host 
	my_addr.sin_family = AF_INET;
	//sequence of the web char , short
	my_addr.sin_port = htons(MYPORT);
	//PUT THE IP INTO THE S_ADDR;
	my_addr.sin_addr.s_addr = INADDR_ANY;

	//set the other space zeros
	bzero(&(my_addr.sin_zero) , 8);
	//check the error
	if (bind(sock_fd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1){
		//When failed to bind ,give the wrong code and exit
		perror("bind");
		exit(1);
	}else{
		printf("bind success\n");
	}

	if(listen(sock_fd, BACKLOG) == -1)
	{
		perror("listen");
		exit(1);
	}

	while(1){
		//This is the mian accept loop
		sin_size = sizeof(their_addr);

		printf("sin_size = %d\n",sin_size);
		printf("sock_fd = %d\n",sock_fd);

		//check the error 
		if ( (new_fd = accept(sock_fd, (struct sockaddr *) &their_addr, &sin_size)) == -1){
		//if ( (new_fd = accept(sock_fd, NULL, NULL)) == -1){
			//If fail to accept ,give the error report and enter the next loop
			printf("%d\n",new_fd);
			perror("accept");
		}
		
		//The server give the connect info
		printf("server: got connection from %s\n", inet_ntoa(their_addr.sin_addr));
		//This will create a son process to connect the socket
		if(!fork()){
			//This is the son process
			if ((numbytes = recv(new_fd, buf, MAXDATASIZE,0)) == -1){
				perror("recv");
				exit(1);
			}else{
				buf[numbytes]='\0';
				printf("%s\n", buf);
			}
			
			//check the error
			char * sendData = "Hello,world\n";
			if(send(new_fd, sendData, strlen(sendData),0) == -1){
				//gave the error report and close the connection when error appears
				perror("send");
				close(new_fd);
				exit(0);
			}else{
				printf("sending the data :  %s; and the lenth of the data is %d \n", sendData, sizeof(sendData));
			}
			//close the new_fd socket
			close(new_fd);
		}
	}
	while(waitpid(-1, NULL, WNOHANG) > 0);

	return 0;
}