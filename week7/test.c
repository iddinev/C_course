#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

int done  = 0;
int cerr = 0;
int perr = 0;

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c  = PTHREAD_COND_INITIALIZER;

void thr_exit() {
    pthread_mutex_lock(&m);
    printf("child1 locked the mutex\n");
    pthread_cond_wait(&c, &m);
    printf("child1 unlocks\n");
    pthread_mutex_unlock(&m);
}

void *child(void* arg) {
    int rank = *(int*)arg;
    thr_exit();
    return NULL;
}

void *child2(void* arg) {
    int rank = *(int*)arg;
    pthread_mutex_lock(&m);
    printf("child2 locked the mutex\n");
    pthread_cond_wait(&c, &m);
    sleep(3);
    printf("child2 unlocks\n");
    /* pthread_mutex_unlock(&m); */
    return NULL;
}

void thr_join() {
    pthread_mutex_lock(&m);
    pthread_cond_broadcast(&c);
    perr = pthread_mutex_unlock(&m);
    printf("mutex unlocked\n");
}

int main(int argc, char* argv[]) {
    printf("parent: begin\n");
    pthread_t p1, p2;
    int r1 = 1;
    int r2 = 2;
    pthread_create(&p2, NULL, child2, (void*)&r2);
    pthread_create(&p1, NULL, child, (void*)&r1);
    printf("parent: end\n");
    sleep(1);
    thr_join();
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    return 0;
}
