#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 50

int main()
{
    /* 使用lseek来计算文件大小 */
    int fd = open("testWhile.c", O_RDONLY);
    if (fd == -1)
    {
        perror("open error");
    }

    // off_t size =  lseek(fd, 0, SEEK_END);
    // printf("size = %ld\n", size);

    char buf[BUFFER_SIZE] = {0};
    lseek(fd, 3, SEEK_SET);
    int ret = read(fd, buf, BUFFER_SIZE);
    if (ret == -1)
    {
        perror("read error");
    }
    printf("buf = %s\n", buf);

    close(fd);
}