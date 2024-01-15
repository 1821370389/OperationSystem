#ifndef __THREAD_POLL_H__
#define __THREAD_POLL_H__

#include <pthread.h>

/* 线程池结构体 */
typedef struct thread_poll_t 
{
    pthread_t *thread_id;   // 线程id数组
    int max_thread_num;     // 最大线程数量
    int min_thr_num;        // 最小线程数量
}
thread_poll_t;

/* 线程池初始化 */
int thread_poll_init(thread_poll_t *thread_poll, int min_thr_num, int max_thr_num);
/* 线程池销毁 */
int thread_poll_destroy(thread_poll_t *thread_poll);
/* 线程池启动 */
int thread_poll_start(thread_poll_t *thread_poll);


#endif //__THREAD_POLL_H__