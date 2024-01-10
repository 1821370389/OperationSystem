#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>


#define PIPE_SIZE 2

int main()
{
    int pipefd[PIPE_SIZE] = {0};
    /* 创建管道 */
    pipe(pipefd);

    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork error");
        exit(-1);
    }

    if(pid == 0)
    {
        /* 子进程 */
        int num = 200;
        /* 关闭读端口,避免僵尸进程 */
        // sleep(5);
        close(pipefd[0]);
        write(pipefd[1], (void *)&num, sizeof(num));
        /* 关闭写端口,回收资源 */
        close(pipefd[1]);
        printf("child num = %d\n", num);
        _exit(-1);
    }
    else
    {
        /* 父进程 */
        int num = 0;
        /* 关闭写端口 */
        close(pipefd[1]);

        /* 父进程 读 */
        /* 把read设置成非阻塞 */
        /* 1. 拿到当前问价描述符的标记 */
        // int flags = fcntl(pipefd[0], F_GETFL);

        // /* 2. 或上O_NONBLOCK */
        // flags |= O_NONBLOCK;

        // /* 3. 用新的标记设置文件描述符 */
        // fcntl(pipefd[0], F_SETFL, flags);
        read(pipefd[0], (void *)&num, sizeof(num));
        /* 关闭读端口,回收资源 */
        close(pipefd[0]);
        printf("parent num = %d\n", num);
    }
    printf("hello world\n");
}