#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>


/* 锁资源 */
pthread_mutex_t g_mutex;

/* 条件变量 */
pthread_cond_t g_noEmpty;       //给消费者发
pthread_cond_t g_noFull;        //给生产者发

/* 链表节点 */
typedef struct Node
{
    int data;
    struct Node *next;
} Node;

/* 链表的头指针 */
Node *head = NULL;
/* 链表的尾指针 */
Node *tail = NULL;

/* 生产者 */
void * producer_thread(void *arg)
{
    int count = 0;
    while(1)
    {
        
        /* 画饼 */
        /* 添加到链表 */
        Node *newNode = (Node *)malloc(sizeof(Node));
        if(newNode == NULL)
        {
            perror("malloc error");
            pthread_exit(NULL);
        }
        memset(newNode, 0, sizeof(Node));
        newNode->data = count++;
        /* 生产者加锁 */
        pthread_mutex_lock(&g_mutex);

        /* 头插 */
        newNode->next = head;
        head = newNode;
        /* 生产者解锁 */
        pthread_mutex_unlock(&g_mutex);
        /* 通知消费者 */
        pthread_cond_signal(&g_noEmpty);
        printf("producer make a pie\n");
        /* 随机休眠 */
        sleep(rand() % 3);

    }
    /* 线程退出 */
    pthread_exit(NULL);

}

/* 消费者 */
void *  consumer_thread(void *arg)
{
    while(1)
    {
        /* 消费者加锁 */
        pthread_mutex_lock(&g_mutex);

        /* 当没有数据的时候，就条件等待；为了与其他消费者竞争，所以用while */
        while(head == NULL)
        {
            /* 等待通知 */
            pthread_cond_wait(&g_noEmpty, &g_mutex);
        }

        /* 吃饼 */
        Node *delNode = head;
        head = head->next;
        /* 消费者解锁 */
        pthread_mutex_unlock(&g_mutex);

        /* 随机休眠 */
        sleep(rand() % 3);
        printf("consumer eat the pie %d\n", delNode->data);
        if(delNode)
        {
            free(delNode);
            delNode = NULL;
        }

        /* 通知生产者 */
        pthread_cond_signal(&g_noFull);

        
        
    }

}

int main(int argc, char *argv[])
{
    /* 初始化锁 */
    pthread_mutex_init(&g_mutex, NULL);
    /* 初始化条件变量 */
    pthread_cond_init(&g_noEmpty, NULL);
    pthread_cond_init(&g_noFull, NULL);

    /* 生产者 */
    pthread_t producer;
    /* 消费者 */
    pthread_t consumer;

    int ret = pthread_create(&producer, NULL, producer_thread, NULL);
    if (ret != 0)
    {
        printf("producer thread create error\n");
        exit(1);
    }
    ret = pthread_create(&consumer, NULL, consumer_thread, NULL);
    if (ret != 0)
    {
        printf("consumer thread create error\n");
        exit(1);
    }


    /* 等待子线程结束 回收线程资源 */
    pthread_join(producer, NULL);
    pthread_join(consumer, NULL);

    /* 释放锁和条件变量 */
    pthread_mutex_destroy(&g_mutex);
    pthread_cond_destroy(&g_noEmpty);
    pthread_cond_destroy(&g_noFull);

    return 0;
}