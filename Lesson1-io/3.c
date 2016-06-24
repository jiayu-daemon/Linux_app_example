#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    int fd = open("1.txt",O_WRONLY|O_APPEND);//追加的方式
    if (fd < 0)
    {
        perror("open");
        exit(1);
    }

    int ret = write(fd,"helloworld",strlen("helloworld"));
    if (ret < 0)
    {
        perror("write");
        exit(2);
    }
    printf("write:%d\n",ret);

    close(fd);
}
