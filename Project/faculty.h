#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
//#include"struct.h"
#include<string.h>
struct course c;
struct{
	int student_count;
	int faculty_count;
	int course_count;
} a;
void add_new_course(int sockfd){
        char readbuffer[1024];
	int fd1=open("db",O_RDWR);
	read(fd1,&a,sizeof(a));
	c.id=a.course_count+1;
	a.course_count=c.id;
	write(fd1,&a,sizeof(a));
        write(sockfd,"Enter the course name:\n",23);
	read(sockfd,c.name,sizeof(c.name));
	write(sockfd,"Enter the faculty name:\n",24);
	bzero(readbuffer,sizeof(readbuffer));
	read(sockfd,c.facultyname,sizeof(c.facultyname));
        bzero(readbuffer,sizeof(readbuffer));
	write(sockfd,"Enter the no of seats:\n",23);
        read(sockfd,readbuffer,sizeof(readbuffer));
        c.seats_offered=atoi(readbuffer);
	c.seat_available=c.seats_offered;
	for(int i=0;i<1000;i++){
		c.arr[i]=0;
	}	
        int fd=open("course_details.txt",O_RDWR|O_CREAT|O_APPEND,0744);
        lseek(fd,c.id*sizeof(struct course),SEEK_SET);
        write(fd,&c,sizeof(c));
}
void remove_course(int sockfd){
	char readbuffer[1024];
	struct course b;
	write(sockfd,"Enter the course id to remove:\n",31);
	read(sockfd,readbuffer,sizeof(readbuffer));
	int id=atoi(readbuffer);
	int fd=open("course_details.txt",O_RDONLY);
	lseek(fd,(id-1)*sizeof(struct course),SEEK_SET);
	c.id=0;
	strcpy(c.name,"NULL");
	strcpy(c.facultyname,"NULL");
	c.seats_offered=0;
}
void login_handle_f(int sockfd){
        char readbuffer[1024];
        char readbuffer_1[1024];
        write(sockfd,"Enter id\n",15);
        bzero(readbuffer,sizeof(readbuffer));
        read(sockfd,readbuffer,sizeof(readbuffer));
        int id=atoi(readbuffer);
        write(sockfd,"Enter password\n",15);


        char password[]="123";
        bzero(readbuffer_1,sizeof(readbuffer_1));
        read(sockfd,readbuffer_1,sizeof(readbuffer_1));
        printf("pasword is %s", readbuffer_1);
        if( strcmp(password,readbuffer_1)==0 ){
                faculty(sockfd);
        }
	else{
		write(sockfd,"Login Unsuccessful\n",19);
	}
}	

void faculty(int sockfd){
        char writebuffer[20];
        begin:
        char a[]="1.Add new Course\n2.Remove offered Course\n3.View enrollments in Courses\n4.Password Change\n5.Exit\nEnter your choice";
        write(sockfd,a,strlen(a));
        bzero(writebuffer,strlen(writebuffer));
        int readbytes=read(sockfd,writebuffer,sizeof(writebuffer));
        int userchoice=atoi(writebuffer);

        switch(userchoice){
                case 1:add_new_course(sockfd);
                       goto begin;
                        break;


                case 2:remove_course(sockfd);
                       goto begin;
                        break;
                case 3:
                       goto begin;
                        break;
                case 4:exit(0);
                        break;
	}
}	



