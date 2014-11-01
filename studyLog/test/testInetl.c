#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

main(){
	struct sockaddr_in  addrSrv;
	addrSrv.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");
	char recvBuf[100];
	char tempBuf[100];
	sprintf(tempBuf,"%s say: %s",inet_ntoa(addrSrv.sin_addr),recvBuf);
	printf("%s",tempBuf);
//将sin_addr储存的IP（数值）转换成字符串形式(127.0.0.1)。
}