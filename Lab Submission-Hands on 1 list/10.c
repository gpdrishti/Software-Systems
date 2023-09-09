#include<stdio.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
int main(){
	int fd;
	char buf[]="1234567890";
	fd=open("read_1.txt",O_RDWR|O_CREAT);
	if(fd<0){
		perror("open");
		return 1;
	}
	write(fd,buf,10);
	int a=lseek(fd,10,SEEK_END);
	printf("lseek returns :%d",a);
	write(fd,buf,10);
	close(fd);
	return 0;
}	

