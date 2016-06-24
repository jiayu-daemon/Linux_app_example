#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>

sem_t ready_go, ready_stop;

void *conductor(void *arg) 
{
	int p = 0;
    printf ("start: door closed\n");
	while (1) 
	{
	    sem_wait(&ready_stop);
        printf("open door\n");
	    printf("up and down ...\n");
		sleep(rand()%5);
        printf("close door\n");
        sem_post(&ready_go);
		sleep(rand()%5);
	}
}

void *driver(void *arg) 
{
	int c = 0;
    printf("start:bus stopped\n");
	while (1) 
	{
	    sem_wait(&ready_go);
        printf ("bus start\n");
	    printf ("bus driving ...\n");
		sleep(rand()%5);
        printf ("bus stop\n");
        sem_post(&ready_stop);
		sleep(rand()%5);
	}
}

int main(int argc, char *argv[]) 
{
	pthread_t conductor_id, driver_id;  
	
	sem_init(&ready_go, 0, 1);
	sem_init(&ready_stop, 0, 0);

	pthread_create(&conductor_id, NULL, conductor, NULL);
	pthread_create(&driver_id, NULL, driver, NULL);
	
	pthread_join(conductor_id, NULL);
	pthread_join(driver_id, NULL);
	
	sem_destroy(&ready_go);
	sem_destroy(&ready_stop);
	return 0;
}
