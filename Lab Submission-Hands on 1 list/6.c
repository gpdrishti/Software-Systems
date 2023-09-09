#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
int main(){
	char buf[13];
	read(0,buf,13);
	write(1,buf,13);
	return 0;
}	
