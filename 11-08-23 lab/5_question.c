#include<stdio.h>
#include<fcntl.h>
void main(){
  for( ; ;){
    int fd1=creat("a.txt",0644);
    int fd2=creat("b.txt",0644);
    int fd3=creat("c.txt",0644);
    int fd4=creat("d.txt",0644);
    int fd5=creat("e.txt",0644);
  }
} 
