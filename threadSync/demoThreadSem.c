#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <semaphore.h>

/* 余量*/
int g_margin = 5;

/* 信号量 */
sem_t g_sem;

/* 抢票 */
void *scrambleForTickets(int num)
{
    sem_wait(&g_sem); //P操作
    g_margin--;
    printf("客户%d 获得一张票\n",num);
    printf("剩余票数：%d\n",g_margin);
    sem_post(&g_sem); //V操作
    usleep(1000); //睡眠0.1秒
}

/* 线程函数1*/
void *thread_fun(void *arg)
{

    /* 抢票客户1 */
    while(g_margin > 0)
    {
        scrambleForTickets(1);
    }
    
    pthread_exit(NULL); //线程退出(返回值为NULL)
}

/* 线程函数2 */
void *thread_fun2(void *arg)
{

    while(g_margin > 0)
    {
        scrambleForTickets(2); //抢票客户2抢票
    }
    pthread_exit(NULL); //线程退出(返回值为NULL)
}


int main()
{

    sem_init(&g_sem,0,1); //初始化信号量为1
    int num = 100;
    pthread_t tid1,tid2;
    int ret = pthread_create(&tid1,NULL,thread_fun,(void*)&num);
    if(ret != 0)
    {
        printf("pthread_create error\n");
        exit(1);
    }
    ret = pthread_create(&tid2,NULL,thread_fun2,(void*)&num);
    if(ret != 0)
    {
        printf("pthread_create error\n");
        exit(1);
    }
    // pthread_mutex_init(NULL,NULL); //初始化互斥锁
    /* 等待回收线程资源 */
    pthread_join(tid1,NULL); //等待线程1退出
    pthread_join(tid2,NULL); //等待线程2退出

    /* 销毁信号量 */
    sem_destroy(&g_sem);

    return 0;

}