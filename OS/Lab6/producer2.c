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

    ptocfd = open(PTOC, O_WRONLY);
    ctopfd = open(CTOP, O_RDONLY);
    itemcount = 5;
    printf("Current item count is 5\n");
    write(ptocfd, &itemcount, sizeof(itemcount));
    while(1)
    {
        read(ctopfd, &itemcount, sizeof(itemcount));
        if(itemcount<MAX)
        {
            printf("Item added, Item count is %d\n", ++itemcount);
            
        }
        else
        {
            printf("FUll\n");
        }
        write(ptocfd, &itemcount, sizeof(itemcount));
        sleep(1);
    }
    close(ctopfd);
    close(ptocfd);

}
