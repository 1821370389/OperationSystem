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
    /* 管道描述符 */
    int pipefd[2] = {0};

    /* 创建管道 */
    pipe(pipefd);

    /* 查看管道缓冲区函数 */
    long bufferSize =  fpathconf(pipefd[0], _PC_PIPE_BUF);
    printf("bufferSize = %ld\n", bufferSize);

    return 0;
}