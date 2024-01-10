/* 有名管道 */
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>


#define BUFFER_SIZE 32
int main()
{
    /* 创建有名管道 */
    /* 有名管道存在于内存中 */
    /* 判断文件是否存在 */
    if(access("./testfifo", F_OK) == -1)
    {
        perror("access error");
        exit(-1);
    }

    int fd = open("./testfifo", O_RDWR);
    if(fd == -1)
    {
        perror("open error");
        exit(-1);
    }
    printf("open success\n");

    char buf[BUFFER_SIZE] = {0};

    if(read(fd, buf, strlen(buf)-1) < 0)
    {
        perror("read error");
        close(fd);
        exit(-1);
    }
    printf("read success\n");
    printf("buf = %s\n", buf);

    close(fd);
    return 0;
}