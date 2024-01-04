#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>


#define BUFFER_SIZE 50

int main()
{

    /* 只读 */
    int fd = open("hello.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("open error");
    }

    char buffer[BUFFER_SIZE] = {0};
    read(fd, buffer, sizeof(buffer)-1);

    printf("buffer: %s\n", buffer);


    close(fd);
    return 0;
}