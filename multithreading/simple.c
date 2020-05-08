#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int point = 0;

void *func(void *val)
{
    pthread_mutex_lock(&mutex);

    int j = point;
    printf("Incrementing point.\n");
    point++;

    pthread_mutex_unlock(&mutex);
    sleep(point);
    printf("Thread %d called!\n", j);
    return NULL;
}

int main(void)
{
    pthread_mutex_init(&mutex, NULL);
    pthread_t thr[3];
    for(int i = 0; i < 3; i++)
        pthread_create(&thr[i], NULL, func, NULL);
    
    pthread_exit(NULL);
    return 0;
}