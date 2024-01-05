#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>


int main()
{
    #if 0
    /* 只写打开文件 */
    int fd = open("hello.txt", O_WRONLY);
    if(fd == -1)
    {
        perror("open error");
    }

    /* 向文件中写数据 */
    char *str = "Hello World";
    write(fd,str,strlen(str));    // 如果此处是strlen(str)+1的话会把'\0'写入文件中,导致文件被识别二进制，无法正常打开

    #elif 1
    /* 清空文件*/
    int fd = open("testOpen Copy.c", O_RDWR | O_TRUNC);
    if(fd == -1)
    {
        perror("open error");
    }
    #elif 1
    /* 向文件中追加数据 */
    int fd = open("hello.txt", O_RDWR | O_APPEND);
    if(fd == -1)
    {
        perror("open error");
    }
    char *str = "\nGood Night World";
    write(fd,str,strlen(str));
    #endif

    close(fd);
    return 0;
}