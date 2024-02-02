#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

#define BUFFER_SIZE 100

int main(int argc, char *argv[])
{

    char ret[BUFFER_SIZE] = {0};
    char *ptr = getcwd(ret, BUFFER_SIZE - 1);   // 获取当前目录
    printf("%s\n", ret);                        // 打印当前目录
    printf("%s\n", ptr);                        // 打印

    return 0;
}