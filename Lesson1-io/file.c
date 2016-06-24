#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main()
{
    int fd = open("1.txt",O_WRONLY|O_APPEND);
    if(fd < 0)
    {
        perror("open");
        exit(1);
    }
    
    int ft =write(fd,"hello",strlen("hello"));
    if(ft < 0)
    {
        perror("write");
        exit(2);
    }
    printf("%d\n",ft);
    close(fd);
}
