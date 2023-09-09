#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define trains 3

struct {
		int train_num;
		int ticket_count;
	} db;

int main()
{
	int fd, input;
	fd=open("records.txt", O_RDWR);
	printf("Select train number(1,2,3): ");
	scanf("%d",&input);
	
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (input-1)*sizeof(db);
    lock.l_len = sizeof(db);  
    lock.l_pid = getpid();
    lseek(fd, (input-1)*sizeof(db), SEEK_SET);
    read(fd, &db, sizeof(db));
    printf("Before Entering into the critical section...\n");
    fcntl(fd, F_SETLKW, &lock);
    printf("Ticket number: %d \n",db.ticket_count);
    db.ticket_count++;
    lseek(fd,-1*sizeof(db),SEEK_CUR);
    write(fd,&db,sizeof(db));
    printf("To book ticket, please press Enter: \n");
    getchar();
    getchar();
    lock.l_type=F_UNLCK;
    fcntl(fd,F_SETLK,&lock);
    printf("Booked...!! with ticket number=%d\n",db.ticket_count);
    close(fd);
    return 0;
}
