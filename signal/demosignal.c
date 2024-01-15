#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>

#define SIZE 50

int main()
{
    /* 注册信号 */
    signal(SIGINT, SIG_IGN);

    while(1)
    {
        printf("hello\n");
        sleep(1);
    }

    return 0;
}