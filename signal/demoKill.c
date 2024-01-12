#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>

#define SIZE 5

int main()
{
    /* 创建进程 */
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork error");
        exit(1);
    }
    if (pid == 0)
    {
        /* 打印PID */
        printf("child process pid: %d\n", getpid());
        /* 子进程 */
        int idx = 0;
        for(idx = 0; idx < SIZE; idx++)
        {
            printf("It's a child process\n");
            sleep(1);
        }
    }
    else
    {   
        /* 打印PID */
        printf("parent process pid: %d\n", pid);
        /* 父进程 */
        printf("It's a parent process\n");
        sleep(2);

        printf("parent  kill child process\n");
        kill(pid, SIGINT);
        printf("parent killed child process\n");
        sleep(2);
    }

    printf("It's a end process\n");

    return 0;
}