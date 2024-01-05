#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
    int ret = rename(argv[1], argv[2]);
    if(ret == -1)
    {
        perror("rename error");
    }
    printf("rename %s to %s\n", argv[1], argv[2]);


    return 0;
}