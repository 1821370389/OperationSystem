#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>


int main()
{
    int num = 100;

    pid_t pid = fork();
    if(pid < 0)
    {
        perror("fork error");
        _exit(-1);
    }

    if(pid == 0)
    {
        /* 子进程 */
        num += 100;
        printf("child process : num = %d\n",num);
        int fd = open("a.txt",O_RDWR | O_CREAT);
        if(fd == -1)
        {
            perror("open error");
            return -1;
        }
        write(fd,(void*)&num,sizeof(num));
        close(fd);

    }
    else
    {
        /* 父进程 */
        printf("parent process : num = %d\n",num);
        sleep(1);
        printf("parent process : num = %d\n",num);
        int fd = open("a.txt",O_RDWR | O_CREAT);
        if(fd == -1)
        {
            perror("open error");
            return -1;
        }
        read(fd,(void*)&num,sizeof(num));
        
        close(fd);
    }

    /* 阻塞等待回收子进程的资源*/
    wait(NULL);

    printf("num = %d\n",num);

    return 0;


}