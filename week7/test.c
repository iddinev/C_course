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
    done = 1;
    pthread_cond_signal(&c);
    /* cerr = pthread_mutex_unlock(&m); */
    /* printf("C ERR %d\n", cerr); */
    /* if (!cerr) { */
        /* printf("mutex_unlock error: child %d\n", cerr); */
    /* } */
}

void *child(void* arg) {
    printf("child\n");
    thr_exit();
    return NULL;
}

void thr_join() {
    pthread_mutex_lock(&m);
    while (done == 0) {
        pthread_cond_wait(&c, &m);
    }
    /* perr = pthread_mutex_unlock(&m); */
    /* printf("P ERR %d\n", perr); */
    perr = pthread_mutex_unlock(&m);
    printf("P ERR %d\n", perr);
    /* if (!perr) { */
        /* printf("mutex_unlock error: parent %d\n", perr); */
    /* } */
}

int main(int argc, char* argv[]) {
    printf("parent: begin\n");
    pthread_t p;
    pthread_create(&p, NULL, child, NULL);
    thr_join();
    printf("parent: end\n");
    pthread_join(p, NULL);
    return 0;
}
