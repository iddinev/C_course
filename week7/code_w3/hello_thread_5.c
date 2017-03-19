#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

#define NUM_THREADS 20

typedef struct {
	int rank;
	char finished1;
	pthread_mutex_t mutex1;
	pthread_cond_t cond1;
	char finished2;
	pthread_mutex_t mutex2;
	pthread_cond_t cond2;
} thread_data;

thread_data td[NUM_THREADS];

void* hello_thread(void *rank) {
	int thread_rank = *(int *)rank;
	if (thread_rank > 0) {
		thread_data *prev = &td[thread_rank - 1];
		pthread_mutex_lock(&prev->mutex1);
		if (!prev->finished1)
			pthread_cond_wait(&prev->cond1, &prev->mutex1);
		pthread_mutex_unlock(&prev->mutex1);
	}

	printf("Hello from thread %d\n", thread_rank);

	if (thread_rank < NUM_THREADS-1) {
		thread_data *curr = &td[thread_rank];
		pthread_mutex_lock(&curr->mutex1);
		curr->finished1 = 1;
		pthread_cond_signal(&curr->cond1);
		pthread_mutex_unlock(&curr->mutex1);
	}

	/* if (thread_rank < NUM_THREADS -1) { */
    if (thread_rank > 0) {
		/* thread_data *next = &td[thread_rank - 1]; */
        thread_data *next = &td[NUM_THREADS - thread_rank];
        pthread_mutex_lock(&next->mutex2);
        if (!next->finished2)
            pthread_cond_wait(&next->cond2, &next->mutex2);
        pthread_mutex_unlock(&next->mutex2);
    }

	printf("Sayonara from thread %d\n", thread_rank);

    /* if (thread_rank < NUM_THREADS -1) { */
    if (thread_rank > 0) {
        thread_data *curr = &td[thread_rank];
        pthread_mutex_lock(&curr->mutex2);
        curr->finished2 = 1;
        pthread_cond_signal(&curr->cond2);
        pthread_mutex_unlock(&curr->mutex2);
    }

	return NULL;
}

int main(void) {
	int rank = 0;
	int err;
	pthread_t thread_ids[NUM_THREADS];

	while(rank < NUM_THREADS) {
		td[rank].finished1 = 0;
		pthread_mutex_init(&td[rank].mutex2, NULL);
		pthread_cond_init(&td[rank].cond2, NULL);
		td[rank].finished2 = 0;
		pthread_mutex_init(&td[rank].mutex2, NULL);
		pthread_cond_init(&td[rank].cond2, NULL);
		rank++;
	}

	rank = 0;
	while(rank < NUM_THREADS) {
		td[rank].rank = rank;

		err = pthread_create(&(thread_ids[rank]), NULL, hello_thread, (void*)&td[rank].rank);
		if (err != 0) {
			printf("Can't create thread error =%d\n", err);
			return 1;
		}
		rank++;
	}

	rank = 0;
	while(rank < NUM_THREADS) {
		pthread_join(thread_ids[rank], NULL);
		rank++;
	}

	rank = 0;
	while(rank < NUM_THREADS) {
		pthread_mutex_destroy(&td[rank].mutex1);
		pthread_cond_destroy(&td[rank].cond1);
		pthread_mutex_destroy(&td[rank].mutex2);
		pthread_cond_destroy(&td[rank].cond2);
		rank++;
	}

	return 0;
}
