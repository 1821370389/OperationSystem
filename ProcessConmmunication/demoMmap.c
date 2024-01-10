/* mmap */
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

#define MMAP_SIZE 1024

int main()
{
    /* 打开文件 */
    int fd =  open("./test.txt", O_RDWR | O_CREAT, 0644);
    if(fd < 0)
    {
        perror("open error");
        _exit(-1);
    }
    void* ptr = mmap(NULL, MMAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED , fd, 0);
    if(ptr == MAP_FAILED)
    {
        perror("mmap error");
        _exit(-1);
    }
    close(fd);
    /*  如果test.txt 被删除的话 会出现 Bus error (core dumped) 错误 物理地址被删
    if(remove("./test.txt") != 0)
    {
        perror("remove error");
        _exit(-1);
    }
    */

#if 0
    /* 从映射好的内存中读取文本 */
    printf("ptr = %s", (char*)ptr);

    /* 向映射好的内存中写入数据 */
    strncpy((char*)ptr, "Hello world!", MMAP_SIZE);
    printf("ptr = %s", (char*)ptr);
#else

    /* 父子进程间的通信 */
    pid_t pid = fork();
    if(pid < 0)
    {
        perror("fork error");
        _exit(-1);
    }
    if(pid == 0)
    {
        /* 子进程 */
        printf("child pid = %d\n", getpid());
        strncpy((char*)ptr, "Hello world!", MMAP_SIZE);
        printf("child ptr = %s\n", (char*)ptr);
        // _exit(0);
    }
    else
    {
        /* 父进程 */
        printf("parent pid = %d\n", getpid());
        wait(NULL);
        printf("parent ptr = %s\n", (char*)ptr);
        // _exit(0);
    }
#endif
    if(munmap(ptr, MMAP_SIZE) == -1)
    {
        perror("munmap error");
        _exit(-1);
    }
    return 0;

}