#ifndef COND_VAR_BARRIER_H
#define COND_VAR_BARRIER_H



// Constants and structs.

typedef struct
{
    pthread_cond_t cond;
    pthread_mutex_t mutex;
    int num_threads;
} barrier;

// *END* Constants and structs.



// Function prototypes:

int barrier_init(barrier *barr, int nthreads);

int barrier_destroy(barrier *barr);

int barrier_wait(barrier *barr);

// *END* Function prototypes.

#endif
