#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
int main(){
	int fd;
	char data[15];
	fd=open("read_2.txt",O_RDONLY);
	if(fd<0){
		perror("open");
	}
	while(!EOF){
		fgets(data,15,\n);
		printf("The Lines data are %s\n",data);
	}
	close(fd);
	return 0;
}	


