// Compute pi using Leibnitz's sum and pthreads.
// The formula is: pi/4 = sum((-1^n)/(2n+1)), n=0,1,...



#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>



#define NUM_THREADS 4


pthread_t thread_id[NUM_THREADS];
int rank[NUM_THREADS];
double partial_pi[NUM_THREADS];
const double acc = 1e-8;



void *partial_sum(void *start_term) {
    int n = *(int *)start_term;
    double sum = 0;
    double summand;
    int sign = 0;
    if (n % 2 == 0) {
        sign = 1;
    }
    else {
        sign = -1;
    }

    do {
        summand = (double)sign / (2 * (double)n + 1);
        sum += summand;
        n+=NUM_THREADS;

	} while (sign * summand >= acc);
    partial_pi[*(int *)start_term] = sum;
    pthread_exit((void *)&partial_pi[*(int *)start_term]);
}

int main() {
    int err;
    double quart_pi = 0;
    double *pt;

    for (int i=0; i<NUM_THREADS; i++) {
        rank[i] = i;
        err = pthread_create(&thread_id[i], NULL, partial_sum, &rank[i]);
        if (err) {
            printf("pthread_create returned %d.\n", err);
            return 1;
        }
    }

    for (int i=0; i<NUM_THREADS; i++) {
        err = pthread_join(thread_id[i], (void **)&pt);
        if (err) {
            printf("pthread_create returned %d.\n", err);
            return 1;
        }
        quart_pi+=*pt;
    }
    printf("pi is = %.10f\n", 4 * quart_pi);

    return 0;
}
