#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
    int num = 0;

    pid_t pid = fork();
    printf("pid = %d\n", pid);
    /* 创建完子进程 */
    if(pid < 0)
    {
        perror("fork error");
        exit(0);
    }
    if(pid == 0)
    {
        /* 确保父进程先执行完 */
        sleep(1);
        num += 10;
        /* 子进程 */
        printf("child process pid = %d\n", getpid());
        printf("num = %d\n", num);                      // 结果为10，说明子进程有独立的运行空间 
        printf("child process ppid = %d\n", getppid());
        int childNum = 666;
        sleep(1);

        int childState = 2;
        while(1)
        {
            printf("child process is running\n");
            sleep(1);
        }
        _exit(childState); // 退出子进程，返回值为childState
    }
    else 
    {
        /* 父进程 */
        printf("parent process pid = %d\n", getpid());
        num += 100;
        printf("num = %d\n", num);
        //printf("childNum = %d \n", childNum); //父函数拿不到子函数的变量

    }
    printf("\n");
    wait(NULL); // 等待子进程结束，父进程才能继续执行
    // int status = 0;
    // // pid_t ret =  wait(&status); // 等待子进程结束，父进程才能继续执行
    // printf("ret = %d\n", ret);
    // printf("status = %d\n", status);
    /* 父子进程都会执行 */
    // printf("Hello world\n");

    return 0;
}