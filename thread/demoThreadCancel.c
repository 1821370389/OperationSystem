#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>



void *tread_func(void *arg)
{
    /* 线程分离 */
    pthread_detach(pthread_self());
    while(1)
    {
        printf("It's a detach thread fun ...\n");
        sleep(1);
    }

    /* 线程退出 */
    pthread_exit(NULL);

}

int main()
{
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, tread_func, NULL);
    if(ret != 0)
    {
        printf("pthread_create error : %s\n", strerror(ret));
        _exit(1);
    }

    while(1)
    {

        sleep(10);
        /* 线程取消 */
        ret = pthread_cancel(tid);
        if(ret != 0)
        {
            printf("pthread_cancel error : %s\n", strerror(ret));
            _exit(1);
        }
        printf("cancel thread ...\n");
        // break;
    }
    return 0;
}