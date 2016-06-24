#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char *argv[])
{
    if(argc != 3)
    {
        printf("bad format!");
        printf("usage:./cp src dest\n");
        exit(1);
    }
    
    char buf[8];
    int ret;
    int fd = open(argv[1],O_RDONLY|O_CREAT);
    if(fd < 0)
    {
        perror("open");
        exit(1);
    }
    
    int fd2 = open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,0644);
    if(fd2 < 0)
    {
        perror("open file2");
        exit(1);
    }

    while((ret = read(fd,buf,sizeof(buf))) > 0)
    {
        write(fd2,buf,ret);        
    }

    close(fd);
    close(fd2);
}
