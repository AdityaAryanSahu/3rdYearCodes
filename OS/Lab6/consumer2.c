#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <limits.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define PTOC "/tmp/ptoc"
#define CTOP "/tmp/ctop"
#define MAX 5

int main()
{
    int ptocfd;
    int ctopfd;
    int itemcount;
    int res;

    if(access(PTOC, F_OK) == -1)
    {
        printf("Creating a fifo\n");
        res = mkfifo(PTOC, 0777);
        if(res == -1)
        {
            printf("fifo failed");
        }
    }
    if(access(CTOP, F_OK) == -1)
    {
        printf("Creating a fifo\n");
        res = mkfifo(CTOP, 0777);
        if(res == -1)
        {
            printf("fifo failed");
        }
    }

    ptocfd = open(PTOC, O_RDONLY);
    ctopfd = open(CTOP, O_WRONLY);
    
    while(1)
    {
        read(ptocfd, &itemcount, sizeof(itemcount));
        if(itemcount>0)
        {
            printf("Item consumed, Item count is %d\n", --itemcount);
            
        }
        else
        {
            printf("Empty\n");
        }
        write(ctopfd, &itemcount, sizeof(itemcount));
        sleep(1);
    }
    close(ctopfd);
    close(ptocfd);

}
