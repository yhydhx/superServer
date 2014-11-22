#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

//define the port user connect to the computer
#define MYPORT 4000
//define the max number not  processed.
#define BACKLOG 10

main(){
	 //use to lisen  to the soket 
	 int sockfd, new_fd;
	 //local message 
	 struct sockaddr_in my_addr;
	 //the info about the connector
	 struct sockaddr_in their_addr;

	 int sin_size;
	 //remember debug
	 sockfd = socket(AF_INET, SOCK_STREAM, 0);
	 //The sequence of the host
	 my_addr.sin_family = AF_INET;

	 //THE SEQUENCE OF THE NET. THE TYPE IS SHORT
	 my_addr.sin_port = htons(MYPORT);

	 //SET THE default ip 
	 my_addr.sin_addr.s_addr = INADDR_ANY;

	//SET THE UNUSED PART ZERO
	bzero(&(my_addr.sin_zero), 8);

	//Don't forget check the bug in your program
	bind(sockfd, (struct sockaddr *) &my_addr, sizeof(struct sockaddr));
	listen(sockfd, BACKLOG);
	sin_size = sizeof(struct sockaddr_in);
	new_fd = accept(sockfd, &their_addr, &sin_size);   
}