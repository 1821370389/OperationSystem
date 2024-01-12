#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>

/* 余量*/
int g_margin = 5;
pthread_mutex_t mutex;


/* 抢票 */
void *scrambleForTickets(int num)
{
    /* 互斥锁 */
#if 0 
    pthread_mutex_lock(&mutex);
#else
    if(pthread_mutex_trylock(&mutex) != 0)
    {
        printf("有人占了客户%d 抢票失败\n",num);
    }
    else
    {
#endif
    g_margin--;
    pthread_mutex_unlock(&mutex);
    printf("客户%d 获得一张票\n",num);
    printf("剩余票数：%d\n",g_margin);
    }
    
    usleep(1000); //睡眠0.1秒
}

/* 线程函数1*/
void *thread_fun(void *arg)
{
    /*
    int num = *(int*)arg;
    printf("thread_fun: %d\n",num); //打印参数
    num += 100;
    *(int*)arg += 100;
    printf("thread_fun: %d\n",num); //打印参数
    */
   
    
    
    /* 抢票客户1 */
    // printf("客户1开始抢票\n");
    while(g_margin > 0)
    {
        scrambleForTickets(1);
    }
    
    pthread_exit(NULL); //线程退出(返回值为NULL)
}

/* 线程函数2 */
void *thread_fun2(void *arg)
{
    /* 
    sleep(1); //睡眠1秒
    printf("thread_fun2: %d\n",*(int*)arg); //打印参数
    */

    /* 抢票客户2 */
    // printf("客户2开始抢票\n");
    while(g_margin > 0)
    {
        scrambleForTickets(2); //抢票客户2抢票
    }
    pthread_exit(NULL); //线程退出(返回值为NULL)
}


int main()
{
    /* 初始化锁 */
    // pthread_mutex_t mutex;
    pthread_mutex_init(&mutex,NULL); //初始化互斥锁
    
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
    /* 销毁锁 */
    pthread_mutex_destroy(&mutex);

}