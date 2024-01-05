#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

#define BUFFER_SIZE 100

int main(int argc, char *argv[])
{

    char ret[BUFFER_SIZE] = {0};
    char *ptr = getcwd(ret, BUFFER_SIZE - 1);
    printf("%s\n", ret);
    printf("%s\n", ptr);

    return 0;
}