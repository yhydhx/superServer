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
#define PORT 1234
#define  UNIXEPOCH 2208988800UL
//the max size we need to receive
#define MAXDATASIZE 1024        

int main(int argc, char * argv[]){
    int sockfd, numbytes;
    int wholebyte;    //the whole file bytes
    int sesc;   //the server socket
    char buf[MAXDATASIZE];
    int createFileFlag = 0; 
    struct hostent *he;
    struct sockaddr_in their_addr;
    FILE *fp;


    if(argc != 2){
        fprintf(stderr, "usage:client hostname\n");
        exit(1);
    }
    if((he = gethostbyname(argv[1])) == NULL){
        herror("gethostbyname");
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

    char * sendData = "serverV1.c dhx";
    if(send(sockfd, sendData, strlen(sendData),0) == -1){
                //gave the error report and close the connection when error appears
                perror("send");
                close(sockfd);
                exit(0);
    }else{
          printf("sending the data :  %s; and the lenth of the data is %d \n", sendData, sizeof(sendData));
    }

//get the whole bytes to prepaer;

/*
    if ((wholebyte = recv(sockfd, buf, MAXDATASIZE,0)) == -1){
            perror("recv");
            exit(1);
    }
*/





    while ((numbytes = recv(sockfd, buf, MAXDATASIZE,0)) ){
        if (numbytes <= 0){
            perror("recv failed");
            close(sockfd);
            exit(0);
        }else{
            buf[numbytes] = '\0';
            if(createFileFlag == 0){
                   fp = fopen("./test.txt", "w+");
                   //fprintf(fp, buf);
                   fputs(buf, fp);
                   fclose(fp);
                   createFileFlag = 1;
            }else{
                   fp = fopen("./test.txt", "a");
                   //fprintf(fp, buf);
                   fputs(buf, fp);
                   fclose(fp);
            }
            printf("%d \n", numbytes);
            
            /*write the bytes to the file*/
            
            //printf(" %s\n",ctime(&now));
            printf("Receive: %s\n", buf);   
        }
         
    }
   
    close(socket);
    return 0;
}