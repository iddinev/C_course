// Implement a pthread barrier using cond variables.
// Rationale: some OS's don't have a native barrier type.



#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

#include"cond_var_barrier.h"



// Constants and structs.

typedef struct
{
    pthread_cond_t *cond_barrier;
    pthread_mutex_t *mutex_barrier;
    int *num_threads;
} barrier;

// *END* Constants and structs.



// Function prototypes:

int barrier_init(const barrier barr)
{
    int errno;

    errno = pthread_cond_init(barr.cond_barrier);
    errno += pthread_mutex_init(barr.mutex_barrier);

    return errno;
}


int barrier_destroy(const pthread_cond_t *cond_barrier,
                    const pthread_mutex_t *mutex_barrier)
{
    int errno;

    errno = pthread_cond_destroy(&cond_barrier);
    errno += pthread_mutex_destroy(&mutex_barrier);

    return errno;
}


int barrier_wait(const pthread_cond_t *cond_barrier,
                 const pthread_mutex_t *mutex_barrier)
{
    int errno;

    errno = pthread_mutex_lock(&mutex_barrier);
    errno += pthread_cond_wait(
}

// *END* Function prototypes.
