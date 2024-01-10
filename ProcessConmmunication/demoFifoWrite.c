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
        int ret = mkfifo("./testfifo", 0664);
        if(ret == -1)
        {
            perror("mkfifo error");
            exit(-1);
        }
    
        printf("mkfifo success\n");
    }

    int fd = open("./testfifo", O_RDWR);
    if(fd == -1)
    {
        perror("open error");
        exit(-1);
    }
    printf("open success\n");

    char buf[BUFFER_SIZE] = {0};
    
    strncpy(buf, "hello world!", sizeof(buf)-1);

    if(write(fd, buf, strlen(buf)) < 0)
    {
        perror("write error");
        close(fd);
        exit(-1);
    }
    printf("write success\n");

    close(fd);
    sleep(10);
    return 0;
}
