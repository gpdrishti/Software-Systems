#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
int main(){
	int fd_1,fd_2;
	fd_1=open("read.txt",O_RDONLY|O_CREAT);
	fd_2=open("write.txt",O_WRONLY|O_CREAT);
	if(fd_1<0 || fd_2<0){
		perror("open");
	}
	while(1){
		char buf;
		int c=read(fd_1,&buf,1);
		if(c==0){
			break;
		}
		write(fd_2,&buf,1);
	}
	close(fd_1);
	close(fd_2);
	return 0;
}	


