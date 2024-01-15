#include "threadPoll.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>

/* 默认最大最小值 */
#define DEFAULT_MIN_THREAD_NUM 0
#define DEFAULT_MAX_THREAD_NUM 10
#define DEFAULT_QUEUE_MAX_SIZE 100

/* 状态码 */
enum STATUS_CODE
{
    SUCCESS = 0,
    NULL_PTR,
    MALLOC_ERROR,
    ACCESS_INVAILD,
    THREAD_CREATE_ERROR,
    UNKNOWN_ERROR,
    
};

/* 线程函数 */
void *threadHander(void *arg)
{
    
}

/* 线程池初始化 */
int thread_poll_init(thread_poll_t *thread_poll, int minSize, int maxSize, int queueCapacity)
{
    if(thread_poll == NULL)
    {
        return NULL_PTR;
    }

    do
    {
        
        /* 判断合法性 */
        if(minSize < 0 || maxSize <= 0 || minSize > maxSize)
        {
            minSize = DEFAULT_MIN_THREAD_NUM;
            maxSize = DEFAULT_MAX_THREAD_NUM;
        }

        /* 更新线程池属性 */
        thread_poll->minSize = minSize;
        thread_poll->maxSize = maxSize;

        /* 队列大小合法性 */
        if(queueCapacity <= 0)
        {
            queueCapacity = DEFAULT_QUEUE_MAX_SIZE;
        }
        thread_poll->queueCapacity = queueCapacity;
        thread_poll->queueSize = 0;
        thread_poll->queueFront = 0;
        thread_poll->queueRear = 0;
        thread_poll->taskQueue = (task_t *)malloc(sizeof(task_t) * queueCapacity);
        if(thread_poll->taskQueue == NULL)
        {
            perror("malloc error");
            break;
        }
        meset(thread_poll->taskQueue, 0, sizeof(task_t) * queueCapacity);
        

        /* 为线程ID分配空间 */
        thread_poll->threadID = (pthread_t *)malloc(sizeof(pthread_t) * maxSize);
        if(thread_poll->threadID == NULL)
        {
            perror("malloc error");
            return MALLOC_ERROR;
        }
        /* 清除脏数据 */
        meset(thread_poll->threadID, 0, sizeof(pthread_t) * maxSize);

        int ret = 0;
        /* 创建线程 */
        for(int idx = 0; idx < minSize; idx++)
        {
            /* 判断ID号是否能够使用 */
            if(thread_poll->threadID[idx] == 0)
            {
                ret = pthread_create((thread_poll->threadID[idx]), NULL, threadHander, NULL);
                if(ret != 0)
                {
                    // perror("pthread_create error");
                    printf("pthread_create error\n");
                    
                    break;
                }
            }

        }
        if(ret != 0)
        {
            break;
        }

        return SUCCESS;
    }while(0);

    /* 程序执行到此，上面一定有bug */
    /* 回收堆空间 */
    if(thread_poll->taskQueue != NULL)
    {
        free(thread_poll->taskQueue);
        thread_poll->taskQueue = NULL;
    }

    /* 回收线程资源 */
    for(int idx = 0; idx < thread_poll->minSize; idx++)
    {
        if(pthread_join(thread_poll->threadID[idx], NULL) != 0)
        {
            pthread_join(thread_poll->threadID[idx], NULL);
        }
    }
    if(thread_poll->threadID != NULL)
    {
        free(thread_poll->threadID);
        thread_poll->threadID = NULL;
    }

    return UNKNOWN_ERROR;
}
/* 线程池销毁 */
int thread_poll_destroy(thread_poll_t *thread_poll);
/* 线程池启动 */
int thread_poll_start(thread_poll_t *thread_poll);