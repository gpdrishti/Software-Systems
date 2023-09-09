#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define trains 3
#define initial 100

int main()
{

	int i,fd;
	struct {
		int train_num;
		int ticket_count;
	} db[trains];
	for(i=0;i<trains;i++)
	{
		db[i].train_num=i+1;
		db[i].ticket_count=initial;
	}
	fd = open("records.txt", O_RDWR|O_CREAT, 0777);
	if (fd == -1) {
        perror("Error opening file for writing");
        return 1;
    }
	
	if( write(fd, &db, sizeof(db)) == -1)
		perror("Cannot write the file...\n");
	close(fd);    
    if (fd == -1) {
        perror("Error opening file for reading");
        return 1;
    }
	return 0;
}
