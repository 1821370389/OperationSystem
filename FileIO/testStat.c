#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <regex.h>      // 正则式
#include <linux/stat.h>



#define BUFFER_SIZE 50

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

int main(int argc, char *argv[])
{
    struct stat bufStat;
    stat("txtCopy.c", &bufStat);
    /*
    printf("File size: %ld\n", bufStat.st_size);
    printf("File mode: %o\n", bufStat.st_mode);
    printf("File inode: %ld\n", bufStat.st_ino);
    printf("File device: %ld\n", bufStat.st_dev);
    printf("File nlink: %ld\n", bufStat.st_nlink);
    printf("File uid: %d\n", bufStat.st_uid);
    printf("File gid: %d\n", bufStat.st_gid);
    printf("File rdev: %ld\n", bufStat.st_rdev);
    printf("File blksize: %ld\n", bufStat.st_blksize);
    printf("File blocks: %ld\n", bufStat.st_blocks);
    */
    
    /* 宏函数判断文件类型 */
    /*
    printf("File type: ");
    switch(bufStat.st_mode & S_IFMT)
    {
        case S_IFBLK:
            printf("block device\n");
            break;

        case S_IFCHR:
            printf("character device\n");
            break;

        case S_IFDIR:
            printf("directory\n");
            break;

        case S_IFIFO:
            printf("FIFO/pipe\n");
            break;

        case S_IFLNK:
            printf("symlink\n");
            break;

        case S_IFREG:
            printf("regular file\n");
            break;

        case S_IFSOCK:
            printf("socket\n");
            break;

        default:
            printf("unknown?\n");
    }
    */
    /* 如何判断文件是否被修改?*/
    /* 1、比较最后修改时间 */
    /* 最后一次访问时间 */
    printf("File atime: ");
    printTime(bufStat.st_atime);
    /* 最后一次修改时间 */
    printf("File mtime: ");
    printTime( bufStat.st_mtime);
    /* 最后一次状态改变时间(如创建文件等），与mtime不同，该值不一定是最后一次修改时间，而是最后一次状态改变时间 */
    printf("File ctime: ");
    printTime(bufStat.st_ctime);

    /* 配置文件 */
    /* 通过代码调用系统函数 */
    // system("ls");

    /* 库函数 */
    FILE *pfd = popen("md5sum testStat.c","r");
    if(pfd == NULL)
    {
        perror("popen error");
        return -1;
    }

    char buf[BUFFER_SIZE] = {0};

    fread(buf, BUFFER_SIZE-1, 1, pfd);

    printf("md5sum: %s", buf);


    pclose(pfd);

    return 0;
}