#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>

#define handle_error_en(en,msg) \
    do{ errno = en; perror(msg); exit(EXIT_FAILURE);}while(0)

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return (void *)1;
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}


void *thr_fn3(void *arg)
{
    int s;
    int i;
    s = pthread_setcancelstate(PTHREAD_CANCEL_DISABLE,NULL);
    if(s != 0)
    {
        handle_error_en(s,"pthread_setcancelstate");
    }
    printf("thread_fn3():cancellation disabled\n");
    while(1) 
    {
        for(i = 0; i < 10; i++)
        {
            printf("thread 3 writing\n");
            sleep(1);
        }
        s= pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);
        if(s != 0)
            handle_error_en(s,"pthread_setcancelsate");
    }
}




int main(void)
{
    pthread_t   tid;
    void        *tret;
	

    pthread_create(&tid, NULL, thr_fn1, NULL);
    pthread_join(tid, &tret);
    printf("thread 1 exit code %d\n", (int)tret);

    pthread_create(&tid, NULL, thr_fn2, NULL);
    pthread_join(tid, &tret);
    printf("thread 2 exit code %d\n", (int)tret);

    pthread_create(&tid, NULL, thr_fn3, NULL);
    sleep(5);

    printf("cancle thr_fn3\n");

    pthread_cancel(tid);
    pthread_join(tid, &tret);

    printf("thread 3 exit code %d\n", (int)tret);

    return 0;
}
