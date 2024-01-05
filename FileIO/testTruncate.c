#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>



int main(int argc, char *argv[])
{
    int ret = truncate("abc",3);
    if(ret == -1)
    {
        perror("truncate error");
        return -1;
    }

    return 0;
}