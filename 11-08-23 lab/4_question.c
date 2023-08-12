#include<stdio.h>
#include<fcntl.h>
void main()
{
   int fd=open("1.txt",O_RDWR);
  printf("fd= %d\n",fd);
}
