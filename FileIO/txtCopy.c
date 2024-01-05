#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 10

int main(int argc, const char *argv[])
{

    if(argc != 3)
    {
        printf("参数应为三个");
        return -1;
    }
    int fd1 = open(argv[1], O_RDONLY);
    int fd2 = open(argv[2], O_WRONLY | O_APPEND | O_CREAT, 0664 );
    if(fd1 == -1 || fd2 == -1)
    {
        perror("open error");
    }

    char buffer[BUFFER_SIZE] = {0};

    int readlen = 0;
    while(1)
    {
        readlen = read(fd1, buffer, BUFFER_SIZE-1);
        if(readlen == 0)
        {
            /* 说明文件读完了 */
            break;
        }
        write(fd2, buffer, readlen);
        if(readlen < BUFFER_SIZE-1 )
        {
            break;
        }
    }

    close(fd1);
    close(fd2);
    return 0;
}