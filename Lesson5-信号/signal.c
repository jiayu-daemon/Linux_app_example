#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void my_func(int sign_no)
{
	if(sign_no==SIGINT)
		printf("I have get SIGINT\n");
	else if(sign_no==SIGQUIT)
		printf("I have get SIGQUIT\n");
}
int main(int argc,char *argv[])
{
	printf("Waiting for signal SIGINT or SIGQUIT \n ");
/*发出相应的信号，并跳转到信号处理函数处*/
	signal(SIGINT, my_func);
	signal(SIGQUIT, my_func);
   if (strcmp (argv[1],"int") == 0)
   {
       raise(SIGQUIT);
   }else
   {
        printf("usage:./a.out int\n");
        exit(1);
   }

   exit(0);
}

