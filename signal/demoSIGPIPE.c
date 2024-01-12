#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define PIPE_SIZE 2

int main()
{
    int pipefd[PIPE_SIZE] = {0};
    
    /* 创建无名管道 */
    if (pipe(pipefd) < 0)
    {
        perror("pipe");
        return -1;
    }

    /* 关闭读端 */
    close(pipefd[0]);

    /* 向管道写入数据 */
    int num = 100;
    /* 向没有读端的管道写数据 */
    if(write(pipefd[1], &num, sizeof(num)) < 0)
    {
        printf("write error\n");
        exit(1);
    }
    sleep(10);
    /* 关闭写端 */
    close(pipefd[1]);

    return 0;
}
/* 
运行结果：
    Program received signal SIGPIPE, Broken pipe.
    SIGPIPE ：管道破损，没有读端的管道写数据
*/