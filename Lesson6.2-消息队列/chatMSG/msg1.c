#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <string.h>
#include <sys/errno.h>
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
	int pid;
    int ret;

	/* 打开（或创建）消息队列 */
	if ((msid = msgget(0x1234, 0666|IPC_CREAT)) < 0) 
	{
		fprintf(stderr, "open msg %X failed.\n", 0x1234);
		return ;
	}
		
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return;
	}

	if (pid > 0)
	{
	
		while(1)
		{
			// 父进程发送
			memset(&buf, 0, sizeof(buf));
			fprintf(stderr, "Please input:");
			/* 从键盘输入消息数据内容 */
			fgets(buf.ctext, sizeof(buf.ctext), stdin);
			if (strncmp(buf.ctext, "exit", 4) == 0)
			{
				break;
			}

			/* 设置消息类型 */
			buf.mtype = 100;		
			/* 发送消息 */
			while ((msgsnd(msid, &buf, strlen(buf.ctext), 0)) < 0)
			{
				if (errno == EINTR) continue;
				return;
			}
		}
		
		/* 设置消息类型 */
		buf.mtype = 50;		
		/* 发送消息 */
		while ((msgsnd(msid, &buf, strlen(buf.ctext), 0)) < 0)
		{
			if (errno == EINTR) continue;
				return;
		}

		
		
	}else
	{
		// 子进程接收
		while(strncmp(buf.ctext, "exit", 4))
		{
			/* 置空消息缓冲区 */
			memset(&buf, 0, sizeof(buf));	
			/* 接收消息 */
			while ((ret = msgrcv(msid, &buf, sizeof(buf.ctext), 50, 0)) < 0)
			{
				if (errno == EINTR) continue;
				return;
			}
			fprintf(stderr, "Msg : Type=%d, Len=%d, Text:%s", buf.mtype, ret, buf.ctext);
		}

	}
}
