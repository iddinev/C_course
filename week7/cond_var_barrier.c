// Implement a pthread barrier using cond variables.
// Rationale: some OS's don't have a native barrier type.



#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

#include"cond_var_barrier.h"



int barrier_init(barrier *barr, int nthreads)
{
    int errno;

    errno = pthread_cond_init(&barr->cond, NULL);
    errno += pthread_mutex_init(&barr->mutex, NULL);

    barr->num_threads = nthreads;

    return errno;
}


int barrier_destroy(barrier *barr)
{
    int errno;

    errno = pthread_cond_destroy(&barr->cond);
    errno += pthread_mutex_destroy(&barr->mutex);

    return errno;
}


int barrier_wait(barrier *barr)
{
    int errno;

    errno = pthread_mutex_lock(&barr->mutex);
    if (barr->num_threads > 1)
    {
        barr->num_threads--;
        errno += pthread_cond_wait(&barr->cond, &barr->mutex);
    }
    else if (barr->num_threads == 1)
    {
        errno +=pthread_cond_broadcast(&barr->cond);
    }
    errno += pthread_mutex_unlock(&barr->mutex);

    return errno;
}

// *END* Function prototypes.
