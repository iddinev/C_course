#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

#define NUM_THREADS 10

void* hello_thread(void *rank) {
	int thread_rank = *(int *)rank;
	printf("Hello from thread %d\n", thread_rank);
	return NULL;
}

int main(void) {
	int rank = 0;
	int err;
	pthread_t thread_ids[NUM_THREADS];

	while(rank < NUM_THREADS) {
		err = pthread_create(&(thread_ids[rank]), NULL, hello_thread, (void*)&rank);
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

	return 0;
}
