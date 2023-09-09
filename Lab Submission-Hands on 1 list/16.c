#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() 
{
    struct flock lock;
    int fd;
    fd=open("locking.txt",O_RDWR|O_CREAT,0766);
    lock.l_type=F_RDLCK;
    lock.l_whence=SEEK_SET;
    lock.l_start=0;
    lock.l_len=0;
    lock.l_pid=getpid();
    printf("Before entering the critical section\n");
    fcntl(fd,F_SETLKW,&lock);
    printf("inside the critical section...\n");
    printf("enter to unlock...\n");
    getchar();
    printf("unlocked\n");
    lock.l_type=F_UNLCK;
    fcntl(fd,F_SETLK,&lock);
    printf("finish\n");
}
