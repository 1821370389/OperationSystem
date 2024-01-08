#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>


int main()
{
    while(1)
    {
        printf("Hello world!\n");
        printf("pid = %d\n", getpid());
        printf("ppid = %d\n", getppid());
        sleep(3);
    }

    return 0;
}