#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>

//define the port we need to connect
#define MYPORT 5000

//DEFINE THE MAX SIZE WE CAN ACCEPT
#define MAXBUFLEN 100

main(){
	int sockfd;
	//localhost info
	struct sockaddr_in my_addr;
	 //address connection info
	 struct sockaddr_in their_addr;
	 int addr_len, numbytes;
	 char buf[MAXBUFLEN];

	 //ge tthe describtion of a socket
	 if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
	 	//if failed to get the socket , report the wrong message and quit
	 	perror("socket");
	 	exit(1);
	 }

	//The sequence of the host 
	my_addr.sin_family = AF_INET;

	my_addr.sin_port = htons(MYPORT);

	my_addr.sin_addr.s_addr = INADDR_ANY;
	bzero(&(my_addr.sin_zero), 8);

	//bind the port 
	if(bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1){
		perror("bind");
		exit(1);
	}

	addr_len = sizeof(struct sockaddr);

	//receive the message
	if ((numbytes = recvfrom(sockfd, buf, MAXBUFLEN, 0, (struct sockaddr *)&their_addr, &addr_len)) == -1){
		perror("recvfrom");
		exit(1);
	}

	//show the message we get
	printf("get the message from  %s\n", inet_ntoa(their_addr.sin_addr));
	printf("packet is %d bytes long\n", numbytes);
	buf[numbytes] = '\0';
	printf("packet contains \"%s\"\n",buf );

	//close the socket
	close (sockfd);
 }