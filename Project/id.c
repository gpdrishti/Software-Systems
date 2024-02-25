#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
int main(){
	struct{
		int student_count;
		int faculty_count;
		int course_count;
	}db;
	db.student_count=0;
	db.faculty_count=0;
	db.course_count=0;
	int fd;
	fd=open("db.txt",O_RDWR|O_CREAT,0644);
	write(fd,&db,sizeof(db));
	close(fd);
}	
