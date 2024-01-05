#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    /* argc 是参数的个数 */
    printf("argc = %d\n", argc);

    if(argc > 1)
    {
        for(int i = 1; i < argc; i++)
        {
            printf("argv[%d]:%s \n", i,argv[i]);
        }
    }

    return 0;
}