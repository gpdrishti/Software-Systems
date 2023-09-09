#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>

int main() {
    fd_set read_fds;
    struct timeval timeout;
    FD_ZERO(&read_fds);
    FD_SET(0, &read_fds);
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    printf("Waiting for input from stdin for up to 10 seconds...\n");
    int ready = select(1, &read_fds, NULL, NULL, &timeout);
    if (ready == -1) 
    {
        perror("Error in select");
        return 1;
    } 
    else if (ready == 0)
        printf("No data received within 10 seconds.\n");
    else
      	if (FD_ISSET(0, &read_fds)) 
            printf("Data is available within 10 seconds!\n");

    return 0;
}
