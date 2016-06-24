#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

void *conductor(void *arg) 
{
	int p = 0;
    printf ("start: door closed\n");
	while (1) 
	{
        printf("open door\n");
	    printf("up and down ...\n");
		sleep(rand()%5);
        printf("close door\n");
		sleep(rand()%5);
	}
}

void *driver(void *arg) 
{
	int c = 0;
    printf("start:bus stopped\n");
	while (1) 
	{
        printf ("bus start\n");
	    printf ("bus driving ...\n");
		sleep(rand()%5);
        printf ("bus stop\n");
		sleep(rand()%5);
	}
}

int main(int argc, char *argv[]) 
{
	pthread_t conductor_id, driver_id;  
	
	pthread_create(&conductor_id, NULL, conductor, NULL);
	pthread_create(&driver_id, NULL, driver, NULL);
	
	pthread_join(conductor_id, NULL);
	pthread_join(driver_id, NULL);
	
	return 0;
}
