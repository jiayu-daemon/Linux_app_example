#include <stdlib.h>
#include <stdio.h>

static void my_exit1(void)
{
		printf("first exit handler \n");
}
static void my_exit2(void)
{
	    printf("second exit handler \n");
}
int main(void)
{
        if(atexit(my_exit2)!=0)
              printf("can¡¯t register myexit2\n");

        if(atexit(my_exit1)!=0)
              printf("can¡¯t register myexit1");

        printf("main is done \n");
        return 0;
}
