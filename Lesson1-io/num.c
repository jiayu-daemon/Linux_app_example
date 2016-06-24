#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int cnt = 0;
    char buff[8];
    int fd = open("1.c",O_RDONLY|O_CREAT,0644);
    if (fd < 0)
    {
        perror("open");
        exit(1);
    }
    int ret;

    while(ret = read(fd,buff,sizeof(buff)) > 0)
    {
        int i;
        for(i = 0; i < 8; i++)
        {
            if(buff[i] == '\n')
            {
				cnt++;
            }
        }
        /*if(buff[0] == '\n')
            cnt++;*/
    }
    if(ret < 0)
    {
        perror("read");
        exit(1);
    }

    close(fd);

    printf("%d\n",cnt);
}
