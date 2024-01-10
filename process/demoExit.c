#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>

int main()
{
    /* 创建进程 */
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork error");
        exit(-1);
    }

    if(pid == 0)
    {
        /* 子进程 */
        printf("child process\n");
        pid_t childPid = getpid();
        printf("child pid = %d\n", childPid);
        exit(0); // 退出子进程，返回值为0
    }
    else if (pid > 0)
    {
        /* 父进程 */
        printf("parent process\n");
        pid_t parentPid = getpid();
        printf("parent pid = %d\n", parentPid);
    }

    printf("hello world\n");

    return 0;
}