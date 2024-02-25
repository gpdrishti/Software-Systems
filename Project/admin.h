#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
struct student s;
struct faculty p;
struct {
	int student_count;
	int faculty_count;
	int course_count;
} d;	
void add_student(int sockfd){
        char readbuffer[1024];
        //write(sockfd,"Enter the id:\n",12);
	int fd1=open("db",O_RDWR);
	//write(sockfd,"#",strlen("#"));
	read(fd1,&d,sizeof(d));
	s.id=d.student_count+1;
	d.student_count=s.id;
	write(fd1,&d,sizeof(d));
	write(sockfd,"Enter the name:\n",16);
	//write(sockfd,"#",strlen("#"));

	read(sockfd,s.name,sizeof(s.name));
	write(sockfd,"Enter the age:\n",15);
	//write(sockfd,"#",strlen("#"));
        bzero(readbuffer,sizeof(readbuffer));
	read(sockfd,readbuffer,sizeof(readbuffer));
	s.age=atoi(readbuffer);
	int fd=open("student_details.txt",O_RDWR|O_CREAT|O_APPEND,0744);
	lseek(fd,s.id*sizeof(struct student),SEEK_SET);
        write(fd,&s,sizeof(s));
	printf("student id is %d", s.id);
	printf("student name is %s", s.name);
	printf("student age is %d", s.age);
}	
void view_student_details(int sockfd){
	char readbuffer[1024];
	write(sockfd,"Enter the id of student to search for\n",37);
	int id;
	struct student d;
	read(sockfd,readbuffer,sizeof(readbuffer));
	id=atoi(readbuffer);
	printf("\n reading id is %d", id);
	int fd=open("student_details.txt",O_RDONLY);
	lseek(fd,(id-1)*sizeof(struct student),SEEK_SET);
	read(fd,&d,sizeof(d));
	bzero(readbuffer,sizeof(readbuffer));

	sprintf(readbuffer,"Student Id: %d\n Student name %s\n Student age %d",d.id, d.name, d.age);
	//write(sockfd,readbuffer,sizeof(readbuffer));
	//printf("student name %s", d.name);
	//write(sockfd,d.name,sizeof(d.name));
	//bzero(readbuffer,sizeof(readbuffer));
	//sprintf(readbuffer,"%d",d.age);
	write(sockfd,readbuffer,sizeof(readbuffer));
}	
void add_faculty(int sockfd){
	char readbuffer[1024];
        int fd1=open("db",O_RDWR);
	read(fd1,&d,sizeof(d));
        p.id=d.faculty_count+1;
	write(fd1,p.id,sizeof(int));
        write(sockfd,"Enter the name:\n",16);
        read(sockfd,p.name,sizeof(p.name));
        write(sockfd,"Enter the age:\n",15);
        read(sockfd,&p.age,sizeof(int));
        int fd=open("faculty_details.txt",O_RDWR|O_CREAT|O_APPEND,0744);
        write(fd,&p,sizeof(p));
}
void login_handle(int sockfd){
	char username[]="IIITB";
	char readbuffer[1024];
	char readbuffer_1[1024];
	write(sockfd,"Enter username\n",15);
	bzero(readbuffer,sizeof(readbuffer));
	read(sockfd,readbuffer,sizeof(readbuffer));
	write(sockfd,"Enter password\n",15);


	char password[]="123";
	bzero(readbuffer_1,sizeof(readbuffer_1));
	read(sockfd,readbuffer_1,sizeof(readbuffer_1));
	if(strcmp(username,readbuffer)==0 && strcmp(password,readbuffer_1)==0 ){
		admin(sockfd);
	}
	else{
		write(sockfd,"Login Unsuccessful\n",19);
	}
}	




void admin(int sockfd){
	char writebuffer[20];
	begin:
	char a[]="1.Add Student\n2.View Student Details\n3.Add Faculty\n4.View Faculty Details\n5.Logout\nEnter your choice";
	write(sockfd,a,strlen(a));
	bzero(writebuffer,strlen(writebuffer));
	//write(sockfd,"#",strlen("#"));
	int readbytes=read(sockfd,writebuffer,sizeof(writebuffer));
	int userchoice=atoi(writebuffer);

	switch(userchoice){
		case 1:add_student(sockfd);
		       goto begin;
			break;


		case 2:view_student_details(sockfd);
		       printf("enter something\n");
		       bzero(writebuffer,sizeof(writebuffer));

		       readbytes=read(sockfd,writebuffer,sizeof(writebuffer));
                       printf("reading bytes %d", readbytes);
	       	       goto begin;
			break;
		case 3:add_faculty(sockfd);
		       goto begin;
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			break;
		case 9:exit(0);
			break;
	}
}	
