#include<stdio.h>
#include<errno.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/ip.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#include"struct.h"
#include"admin.h"
#include"faculty.h"
#include"student.h"
void connection_handler(int connfd); 
void main(){
	int sfd,cfd;
	struct sockaddr_in serverAddress,clientAddress;
	sfd=socket(AF_INET,SOCK_STREAM,0);
	serverAddress.sin_family=AF_INET;
	serverAddress.sin_port=htons(4455);
	serverAddress.sin_addr.s_addr=htonl(INADDR_ANY);
	bind(sfd,(struct sockaddr*)&serverAddress,sizeof(serverAddress));
	listen(sfd,10);
	int clientSize;
	while(1){
		clientSize=(int)sizeof(clientAddress);
		cfd=accept(sfd,(struct sockaddr*)&clientAddress,&clientSize);
		if(!fork()){
			connection_handler(cfd);
			close(cfd);
		}
	}
	close(sfd);
}
void connection_handler(int connectionFileDescriptor){
	printf("Client has connected\n");
	char readBuffer[1000],writeBuffer[1000];
	ssize_t readBytes,writeBytes;
	int userchoice;
	char start[]="welcome to academia portal\nLogin as \nenter 1 for admin\nenter 2 for professor\nenter 3 for student";
	writeBytes=write(connectionFileDescriptor,start,strlen(start));
	bzero(readBuffer,sizeof(readBuffer));
	//write(connectionFileDescriptor,"#",strlen("#"));
	readBytes=read(connectionFileDescriptor,readBuffer,sizeof(readBuffer));
	userchoice=atoi(readBuffer);
	switch(userchoice){
		case 1://Admin
		       //admin(connectionFileDescriptor);
		       login_handle(connectionFileDescriptor);
		       break;
		case 2://Faculty
		       login_handle_f(connectionFileDescriptor);
		       break;
		case 3://Student
		       login_handle_s(connectionFileDescriptor);
		       break;
		default:
		       break;
	}
	printf("close the connection in client\n");
}	

