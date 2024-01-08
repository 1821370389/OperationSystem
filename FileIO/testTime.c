#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>


/* 调试标记是否存在 */
int g_debug = 0;

/* 打印时间 */
void printTime(time_t t)
{
    struct tm *tm;
    tm = localtime(&t);
    printf("%02d-%02d-%02d %02d:%02d:%02d\n", 
    tm->tm_year + 1900, 
    tm->tm_mon + 1, 
    tm->tm_mday, 
    tm->tm_hour, 
    tm->tm_min, 
    tm->tm_sec);
}

/* 日志：就是文件 */
/* 打开日志文件 */
void log_init(const char *log_path)
{
    time_t now;

    struct tm *ptm = NULL;
#define DEBUF_FLAG "./my_debug.flag"

    if(access(DEBUF_FLAG, F_OK) == 0)
    {
        g_debug = 1;
    }

    if(!g_debug)
    {
        return;
    }
#define DEBUF_FILE "./my_debug.log"

}

int main()
{
    struct tm *info = localtime(NULL);
    printf("%d\n", info->tm_year);
    printf("%d\n", info->tm_mon);
}