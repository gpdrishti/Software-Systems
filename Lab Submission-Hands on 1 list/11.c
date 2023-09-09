#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
int main(){
	int old_fd,new_fd;
	old_fd=open("read_3.txt",O_RDWR|O_CREAT);
	printf("old file descriptor: %d",old_fd);
	new_fd=dup(old_fd);
	printf("new file descriptor:%d",new_fd);
	write(old_fd,"data written by old descriptor",30);
	write(new_fd,"data written by new descriptor",30);
	dup2(old_fd,1);
	printf("Now 1 has become file descriptor for file read_3.txt,so any thing printf prints will be printed in read_3.txt file");
	return 0;
}	
