#include <unistd.h>
#include <stdlib.h>

int main(void)
{
	pid_t pid=fork();
	if(pid<0) {
		perror("fork");
		exit(1);
	}
	if(pid>0) { /* parent */
		while(1);
	}
	/* child */
	return 0;	  
}