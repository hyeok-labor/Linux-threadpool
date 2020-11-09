#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <assert.h>

#include "threadpool.h"

#define THREAD 5
#define QUEUE 10

int task = 0;
int done = 0;
pthread_mutex_t lock;

void dummy_task(void *arg)
{
    usleep(10000);
    pthread_mutex_lock(&lock);
    ++done;
    pthread_mutex_unlock(&lock);
}

int main(int argc, char **argv)
{
    threadpool_t *pool;
    // dommy(done)
    pthread_mutex_init(&lock, NULL);

    // pool = threadpool_create(THREAD,QUEUE,0);
    // assert(pool != NULL);
    assert((pool = threadpool_create(THREAD, QUEUE, 0)) != NULL);
    fprintf(stderr, " pool started with %d threads and queue size of %d\n", THREAD, QUEUE);

    while (threadpool_add(pool, &dummy_task, NULL, 0) == 0)
    {
        pthread_mutex_lock(&lock);
        ++task;
        pthread_mutex_unlock(&lock);
    }

    fprintf(stderr, " added %d task\n", task);

    while ((task / 2) > done)
    {
        usleep(1000);
    }
    assert(threadpool_destroy(pool, 0) == 0);
    fprintf(stderr, " did %d tasks\n", done);

    pthread_mutex_destroy(&lock);
    return 0;
}