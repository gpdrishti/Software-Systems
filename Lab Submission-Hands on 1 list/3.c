#include<stdio.h>
#include<fcntl.h>
void main(){
   int fd=creat("1.txt",0644);
   printf("fd= %d\n",fd);
}
