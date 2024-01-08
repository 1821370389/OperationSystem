#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

#include <dirent.h>


#define BUFFER_SIZE 128

int main(int argc, char *argv[])
{
    char buffer[BUFFER_SIZE] = {0};
    /* 获取当前文件目录 */
    getcwd(buffer, BUFFER_SIZE-1);
    /* 打开指定目录 */
    DIR *pDir =  opendir(buffer);
    if (pDir == NULL)
    {
        perror("打开文件夹失败");
        return -1;
    }
    /* 读取目录中的文件 */
    struct dirent *pDirent = NULL;
    while ((pDirent = readdir(pDir)) != NULL)
    {
        if(!S_ISREG(pDirent->d_type))
        {
            printf("文件夹\n");
        }
        printf("文件名:%s\n", pDirent->d_name);
        printf("文件类型:%d\n", pDirent->d_type);
        printf("文件大小:%d\n", pDirent->d_reclen);
        printf("\n");
    }
    /* 关闭目录 */
    closedir(pDir);

    return 0;
}