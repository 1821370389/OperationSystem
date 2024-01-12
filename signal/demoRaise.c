#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>

#define SIZE 50

int main()
{
    for(int idx = 0; idx < SIZE; idx++)
    {
        if(idx == 15)
        {
            raise(SIGTERM);
            // 等价于
            //  kill(getpid(), SIGTERM);

        }
        printf("idx = %d\n", idx);
        usleep(50000);
    }

    return 0;
}