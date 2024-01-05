#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>



int main(int argc, char *argv[])
{

    /* 检测文件是否存在 */
    int ret  = access("./abc.c", F_OK);
    if(ret != 0)
    {
        perror("access error");
    }

    return 0;
}