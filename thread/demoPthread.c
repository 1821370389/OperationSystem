/* 多线程id */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>


typedef struct stuInfo
{
    char name[20];
    int age;
    char sex;
} stuInfo;

/* 线程1的函数 */
void *thread_func(void *arg)
{
    /* 线程分离 */
    pthread_detach(pthread_self());
    printf("This is thread_func\n");
    sleep(5);
    printf("arg = %d\n", *(int*)arg);
}

/* 线程2的函数 */
void *thread_func2(void *arg)
{
    printf("This is thread_func2\n");
    printf("arg.name: %s,arg.age:%d.arg.sex:%s\n",
    ((stuInfo*)arg)->name, ((stuInfo*)arg)->age, (((stuInfo*)arg)->sex == 'M')?"男":"女");
    sleep(6);
    static int retVal = 67;
    pthread_exit((void*)&retVal);
}

int main()
{   
    /* 获取线程tid */
    pthread_t tid = pthread_self();
    printf("tid = %lu\n", tid);
    printf("pid = %d\n", getpid());     // pid != tid

    /* 创建新线程 */
    pthread_t tid1;
    int num = 250;
    if(pthread_create(&tid1, NULL, thread_func, (void*)&num) != 0)
    {
        printf("pthread_create error:%s\n",strerror(errno));    // 输出错误信息 不能用perror
        _exit(1);
    }
    pthread_t tid2;
    stuInfo stu = {"zhangsan", 18, 'M'};
    if(pthread_create(&tid2, NULL, thread_func2, (void*)&stu) != 0)
    {
        printf("pthread_create error:%s\n",strerror(errno));    // 输出错误信息 不能用perror
        _exit(1);
    }
    printf("tid2 = %lu\n", tid2);


    /* 比较两线程是否相等 */
    if(pthread_equal(tid, tid2))        // 返回值是int,成功非零，败则是0
    {
        printf("tid == tid2\n");
    }
    else
    {
        printf("tid != tid2\n");
    }

    /* 返回的退出值 */
    int *retVal = NULL;
    /* join 的返回值 */
    int ret = 0;

    
    /* 等待线程结束 */
    sleep(1);
    ret = pthread_join(tid1, NULL);           // tid1线程已经被分离了，即时join了也不会阻塞
    if(ret != 0)
    {
        printf("pthread_join error:%s\n",strerror(errno));    // 输出错误信息 不能用perror
    }
    printf("tid1 is over\n");
    ret = pthread_join(tid2, (void**)&retVal);
    if(ret != 0)
    {
        printf("pthread_join error:%s\n",strerror(errno));    // 输出错误信息 不能用perror
    }
    printf("tid2 is over\n");
    
    printf("retVal = %d\n", *retVal);

    return 0;
}
