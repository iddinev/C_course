#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

#define NUM_THREADS 10

typedef struct {
	int rank;
	char finished;
	pthread_mutex_t mutex;
	pthread_cond_t cond;
} thread_data;

thread_data td[NUM_THREADS];

void* hello_thread(void *rank) {
	int thread_rank = *(int *)rank;
	if (thread_rank > 0) {
		thread_data *prev = &td[thread_rank - 1];
		pthread_mutex_lock(&prev->mutex);
		if (!prev->finished)
			pthread_cond_wait(&prev->cond, &prev->mutex);
		pthread_mutex_unlock(&prev->mutex);
	}

	printf("Hello from thread %d\n", thread_rank);

	if (thread_rank < NUM_THREADS-1) {
		thread_data *curr = &td[thread_rank];
		pthread_mutex_lock(&curr->mutex);
		curr->finished = 1;
		pthread_cond_signal(&curr->cond);
		pthread_mutex_unlock(&curr->mutex);
	}

	return NULL;
}

int main(void) {
	int rank = 0;
	int err;
	pthread_t thread_ids[NUM_THREADS];

	while(rank < NUM_THREADS) {
		td[rank].finished = 0;
		pthread_mutex_init(&td[rank].mutex, NULL);
		pthread_cond_init(&td[rank].cond, NULL);
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
		pthread_mutex_destroy(&td[rank].mutex);
		pthread_cond_destroy(&td[rank].cond);
		rank++;
	}

	return 0;
}
