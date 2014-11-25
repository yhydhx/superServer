/****************************************
 *@author jupiter dai 			           *
 *this server is for neibour box's  registing         *
 ****************************************/



#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>

#define PATH_MAX 128

 /*******************
  *    MAIN FUNCTION *
  *******************/

  int main(int argc, char ** argv){
  	int port = 1234;			//port number to user
  	int sock ; 			//socket desciptor
  	int desc;			//file descriptor for socket
  	int fd;				//file descriptor for file to send
  	struct sockaddr_in addr;		//socketparameters for bind
  	struct sockaddr_in addr1;	//socket parameters for accept
  	int addrlen;			//argument to accept
  	struct stat stat_buf;		//argument to fstat
  	off_t  offset = 0;			//file offset
  	char userInfo[PATH_MAX]; 	//FILENAME TO SEND
  	int  rc;				//holds return code of system calls
  	char fileSize[24];		//record the size of buffer;
  	char* username =  NULL;		//record the username
  	char* password = NULL;		//record the password
  	char* sendData;		//send the message to the client

  	/***********************************************
		check the command line aruguments.                *
  	  ***********************************************/
	if (argc == 2){
		port = atoi(argv[1]);
		if(port <= 0){
			fprintf(stderr, "invalid port : %s\n", argv[1] );
			exit(1);
		}
	}else if (argc != 1){
		fprintf(stderr, "usage: %s [port] \n", argv[0]);
		exit(1);
	}

	/*create Internet domain socket*/
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1){
		fprintf(stderr, "unable to create socket : %s\n", strerror(errno));
	}

	/*fill in socket structure*/
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr  = INADDR_ANY;
	addr.sin_port = htons(port);


	/*bind socket to the port*/
	rc = bind(sock, (struct sockaddr *)&addr, sizeof(addr));
	if (rc == -1){
		fprintf(stderr, "unable to bind to socket %s\n", strerror(errno));
		exit(1);
	}

	/*listen for clients on the socket */
	rc = listen(sock ,1);
	if (rc == -1){
		fprintf(stderr, "listen failed : %s\n", strerror(errno));
		exit(1);
	}

	while(1){
		/*   wait for a client to connect */
		desc = accept(sock, (struct sockaddr *)&addr1, &addrlen);
		if(desc == -1){
			fprintf(stderr, "accept failed : %s\n", strerror(errno));
			exit(1);
		}

		/*   get the username and password from the client */
		rc = recv(desc, userInfo, sizeof(userInfo), 0 );
		if (rc == -1){
			fprintf(stderr, "recv failed : %s\n", strerror(errno));
			exit(1);
		}else{
			if (userInfo[strlen(userInfo) -1] == '\n' || userInfo[strlen(userInfo) - 1] == '\r'){
				userInfo[strlen(userInfo) -1 ] = '\0';			}
		}

		printf("get the data, then analyze it %s\n" , userInfo);
		/*process the username and the password */
		if (strlen(userInfo) == 0){
			// when the data is null send the false message to the client
			strcpy(sendData , "false");
			if(send(desc, sendData, strlen(sendData),0) == -1){
				//gave the error report and close the connection when error appears
				perror("send");
				close(desc);
				exit(0);
			}else{
				printf("sending the data :  %s; and the lenth of the data is %d \n", sendData, strlen(sendData));
			}
		}else{
			//whne the data is correct 
			printf("%s\n",userInfo);

			username = strtok(userInfo," ");
			char ch = *username;
			printf("%caa\n", ch );
			printf("hello \n%s\n",username);

			password = strtok(NULL,"");
			printf("hellowr \n%s\n",password);
			strcpy(sendData , "true userId" );
			if(send(desc, sendData, strlen(sendData),0) == -1){
				//gave the error report and close the connection when error appears
				perror("send");
				close(desc);
				exit(0);
			}else{
				printf("sending the data :  %s; and the lenth of the data is %d \n", sendData, strlen(sendData));
			}
		}
	}

  }