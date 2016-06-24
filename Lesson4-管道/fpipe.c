#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define BUFSIZE 1024

int main()
{
	FILE *fp;
	char *cmd = "printenv";
	char buf[BUFSIZE];
	buf[BUFSIZE-1] = '\0';	

	if((fp=popen(cmd,"r"))==NULL)
    {
		perror("popen");	
    }

	while((fgets(buf,BUFSIZE,fp))!=NULL)
    {
		printf("%s",buf);
    }

	pclose(fp);
	exit(0);
}
