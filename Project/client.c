#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
void connection_handler(int sockfd);

#define PORT 4455
void main(){
	int clientSocket;
	struct sockaddr_in serverAddr;
	char buffer[1024];

	clientSocket=socket(AF_INET,SOCK_STREAM,0);
	serverAddr.sin_family=AF_INET;
	serverAddr.sin_port=htons(PORT);
	serverAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	connect(clientSocket,(struct sockaddr*)&serverAddr,sizeof(serverAddr));
	connection_handler(clientSocket);
	close(clientSocket);
}	
void connection_handler(int sockfd){
	char readbuffer[1000],writebuffer[1000];
	ssize_t readbytes,writebytes;
	char tempbuffer[1000];
	do{
		bzero(readbuffer,sizeof(readbuffer));
		bzero(tempbuffer,sizeof(tempbuffer));
		readbytes=read(sockfd,readbuffer,sizeof(readbuffer));
		if(readbytes==-1){
			perror("error while reading from client socket");
		}	
		else if(readbytes==0){
			printf("no error received from server");
		}
		else if(strchr(readbuffer,'^')!=NULL){
			strcpy(tempbuffer,readbuffer);
			printf("%s\n",tempbuffer);
			writebytes=write(sockfd,"^",strlen("^"));
		}
		else if(strchr(readbuffer,'$')!=NULL){
			strcpy(tempbuffer,readbuffer);
			printf("%s\n",tempbuffer);
			printf("closing the connection to the server now!\n");
			break;
		}

		else{
			bzero(writebuffer,sizeof(writebuffer));
			if(strchr(readbuffer,'#')!=NULL){
				strcpy(writebuffer,getpass(readbuffer));
			}
			else{
				printf("%s\n",readbuffer);
				scanf("%s",writebuffer);
			}
			writebytes=write(sockfd,writebuffer,strlen(writebuffer));
		}
	}while(readbytes>0);
}	


