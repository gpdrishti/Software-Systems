#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
int main(){
	int fd,accessmode;
	fd=open("read_4.txt",O_RDONLY|O_CREAT);
	int c=fcntl(fd,F_GETFL);
	if(c==-1){
		return 1;
	}
	if(c & O_SYNC){
		printf("writes are synchronized\n");
	}
	accessmode=c &O_ACCMODE;
	if(accessmode == O_RDONLY){
		printf("file is readonly");
	}
	else if(accessmode == O_WRONLY || accessmode ==O_RDWR){
		printf("file is writable \n");
	}	
	printf("c is:%d",c);
	return 0;
}
