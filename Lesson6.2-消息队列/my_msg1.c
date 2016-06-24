#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <string.h>
#include <sys/errno.h>
#include <unistd.h>
#include <stdlib.h>

extern int errno;
struct mymsgbuf 			/* 定义消息结构 */
{
    long	mtype;   		/* 消息类型 */
    char	ctext[100];		/* 消息数据 */
}; 

int main()
{
    struct mymsgbuf buf;	/* 申请消息缓冲 */
    int msid;
    pid_t pid;
    int ret;

    /* 打开（或创建）消息队列 */
    if ((msid = msgget(0x1234, 0666|IPC_CREAT)) < 0) 
    {
        fprintf(stderr, "open msg %X failed.\n", 0x1234);
        return ;
    }

    pid = fork();
    if(pid < 0)
    {
        perror("fork error!\n");
        exit(2);
    }
    else if(pid == 0)
    {
        // 子进程发送消息

        while(strncmp(buf.ctext, "exit", 4))
        {
            sleep(1);
            memset(&buf, 0, sizeof(buf));
            fprintf(stderr, "Please input:");
            /* 从键盘输入消息数据内容 */
            fgets(buf.ctext, sizeof(buf.ctext), stdin);
            /* 设置消息类型 */
            buf.mtype = 12;		
            /* 发送消息 */
            while ((msgsnd(msid, &buf, strlen(buf.ctext), 1)) < 0)
            {
                if (errno == EINTR) continue;
                return;
            }
        }

    }
    else
    {
        //父进程接收消息
        while(strncmp(buf.ctext, "exit", 4))
        {
            sleep(1);
            /* 置空消息缓冲区 */
            memset(&buf, 0, sizeof(buf));
            /* 接收消息 */
            while ((ret = msgrcv(msid, &buf, sizeof(buf.ctext), 11, 0)) < 0)// 0 
            {
                if (errno == EINTR) continue;
                return;
            }
            fprintf(stderr, "Msg : Type=%ld, Len=%d, Text:%s", buf.mtype, ret, buf.ctext);
        }


    }
}


