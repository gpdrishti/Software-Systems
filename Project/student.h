#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
void enroll_in_new_course(int sockfd,int student_id){
	char readbuffer[1024];
	write(sockfd,"Enter id\n",15);

	bzero(readbuffer,sizeof(readbuffer));
	read(sockfd,readbuffer,sizeof(readbuffer));
	int id=atoi(readbuffer);
	int fd=open("course_details.txt",O_RDONLY);
	struct flock read_lock;
        read_lock.l_type = F_RDLCK;
        read_lock.l_whence = SEEK_SET;
        read_lock.l_start = (id - 1) * sizeof(struct course);
        read_lock.l_len = sizeof(struct course);

        fcntl(fd, F_SETLKW, &read_lock);

	lseek(fd,(id-1)*sizeof(struct course),SEEK_SET);
	struct course b;
	read(fd,&b,sizeof(b));
	b.seat_available-=1;

	b.arr[student_id]=1;
	write(fd,&b,sizeof(b));
}
void login_handle_s(int sockfd){
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
                student(sockfd,id);
        }
        else{
                write(sockfd,"Login Unsuccessful\n",19);
        }
}	
void student(int sockfd,int student_id){
        char writebuffer[20];
        begin:
        char a[]="1.Enroll to new course\n2.Unenroll from already registered course\n3.View enrolled  Courses\n4.Password Change\n5.Exit\nEnter your choice";
        write(sockfd,a,strlen(a));
        bzero(writebuffer,strlen(writebuffer));
        int readbytes=read(sockfd,writebuffer,sizeof(writebuffer));
        int userchoice=atoi(writebuffer);

        switch(userchoice){
                case 1:enroll_in_new_course(sockfd,student_id);
                       goto begin;
                        break;


                case 2:
                       goto begin;
                        break;
                case 3:
                       goto begin;
                        break;
                case 4: exit(0);
                        break;
        }
}





