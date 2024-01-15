#ifndef __THREAD_POLL_H__
#define __THREAD_POLL_H__

#include <pthread.h>

/* 任务结构体 */
typedef struct task_t
{
    void *(*function)(void *);
    void *arg;
    struct task_t *next;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}task_t;

/* 线程池结构体 */
typedef struct thread_poll_t 
{
    task_t *taskQueue;     // 任务队列
    int queueCapacity;        // 任务队列容量
    int queueSize;            // 任务队列大小
    int queueFront;           // 队列头
    int queueRear;            // 队列尾

    pthread_t *threadID;   // 线程id数组
    int maxSize;        // 最大线程数量
    int minSize;        // 最小线程数量
}
thread_poll_t;

/* 线程池初始化 */
int thread_poll_init(thread_poll_t *thread_poll, int minSize, int maxSize, int queue_max_size);
/* 线程池销毁 */
int thread_poll_destroy(thread_poll_t *thread_poll);
/* 线程池启动 */
int thread_poll_start(thread_poll_t *thread_poll);


#endif //__THREAD_POLL_H__