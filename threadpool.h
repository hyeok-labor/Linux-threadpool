#ifndef THREADPOOL_H
#define THREADPOOL_H

#define MAX_THREADS 32
#define MAX_QUEUE 1024

typedef struct threadpool_t threadpool_t;

typedef enum
{
    threadpool_invalid = -1,
    threadpool_lock_failure = -2,
    threadpool_queue_full = -3,
    threadpool_shutdown = -4,
    threadpool_thread_failure = -5
} threadpool_error_t;

typedef enum
{
    threadpool_graceful = 1
} threadpool_destroy_flags_t;

threadpool_t *threadpool_create(int thread_count, int queue_size, int flags);

int threadpool_add(threadpool_t *pool, void (*routine)(void *),
                   void *arg, int flags);

int threadpool_destroy(threadpool_t *pool, int flags);

#endif /*THREADPOOL_H*/
