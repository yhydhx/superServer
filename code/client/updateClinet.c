/************************************************
 *@author jupiter dai 			           		*
 *this client is for neibour box's  update transfering         *
 ************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <time.h>
//define the port we listen
#define PORT 4001
//the max size we need to receive
#define MAXDATASIZE 100

int main(int argc, char * argv[]){
	int sockfd, numbytes;
	char buf[MAXDATASIZE];

	struct hostent *he;
	struct sockaddr_in their_addr;

	char* header;
	char* name;
	char* type;
	char* shareFileId;
	char* osId;
	char* modRecord;
	char sendData[1024] = "";

	if(argc != 8){
		fprintf(stderr, "usage:client hostname Header Name Type ShareFile_Id OS_ID, Mod_Record\n");
		exit(1);
	}
	/**
	 * Get the eight param from the User
	 */
	
	//get the host name 
	if((he = gethostbyname(argv[1])) == NULL){
		herror("gethostbyname");
		exit(1);
	}
	//get the Header
	if((header = argv[2]) == NULL){
		herror("get Header");
		exit(1);
	}
	//get the name
	if((name = argv[3]) == NULL){
		herror("get Name");
		exit(1);
	}
	//get the type
	if((type = argv[4]) == NULL){
		herror("get Type");
		exit(1);
	}
	//get the shareFile_ID
	if((shareFileId = argv[5]) == NULL){
		herror("get ShareFile_Id");
		exit(1);
	}
	//get the SynID
	if((osId = argv[6]) == NULL){
		herror("get OS_ID");
		exit(1);
	}
	//get the FileRes_OS_ID
	if((modRecord = argv[7]) == NULL){
		herror("get Mod_Record");
		exit(1);
	}

	if((sockfd = socket(AF_INET, SOCK_STREAM,0)) == -1){
		perror("socket");
		exit(1);
	}

	//sequence of the host
	their_addr.sin_family = AF_INET;

	their_addr.sin_port = htons(PORT);
	their_addr.sin_addr = *((struct in_addr *) he->h_addr);
	bzero(&(their_addr.sin_zero), 8);

	if(connect(sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1){
		perror("connect");
		exit(1);
	}
	//send the data ~
	printf("helloworld\n");
	for(int i=2;i < 8; i++){
		strcat(sendData, argv[i]);
		strcat(sendData, " ");
		printf("%s\n", sendData);
	}
	sendData[strlen(sendData)-1] = '\0';
	printf("%s\n", sendData);
	//sprintf(sendData, "%s %s %s %s %s %s", argv[2],argv[3],argv[4],argv[5],argv[6],argv[7]);
	printf("end helloworld \n");
	if(send(sockfd, sendData, strlen(sendData),0) == -1){
		perror("send");
		close(sockfd);
		exit(0);
	}
	if ((numbytes = recv(sockfd, buf, MAXDATASIZE,0)) == -1){
		perror("recv");
		exit(1);
	}
	//printf("%d \n", numbytes);
	buf[numbytes] = '\0';
	close(socket);
	return 0;
}