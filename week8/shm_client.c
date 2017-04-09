#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#define SEM_NAME "shm"
#define SEM_SIG_NAME "shm_sig"
#define FTOK_NAME "shm_server"

int main() {
	int shmid;
	key_t key;
	char *data, *ch;
	sem_t *sem;
	sem_t *sem_sig;

	/* open and initialize existing semaphore */
	sem = sem_open(SEM_NAME, 0, 0644, 0);
	if(sem == SEM_FAILED) {
		perror("semopen()");
		sem_close(sem);
		return 1;
  	}
	sem_sig = sem_open(SEM_SIG_NAME, 0, 0644, 0);
	if(sem == SEM_FAILED) {
		perror("semopen()");
		sem_close(sem_sig);
		return 1;
  	}

	/* get key for the shared memory segment */
        key = ftok(FTOK_NAME, 33);


	/* create or get shared memory segment with this key */
	shmid = shmget(key, 0, 0);
	if(shmid == -1) {
		perror("shmget()");
		return 1;
	}

	/* map this segment to the virtual memory */
	data = shmat(shmid, NULL, 0);

	/* start reading */
	for(ch = data; *ch != 0; ch++) {
		sem_wait(sem);
		putchar(*ch);
		sem_post(sem);
	}
	putchar('\n');

	/* once done notify server by writing # at the beginiing of the buffer */
    sem_post(sem_sig);
	/* *data = '#'; */

	/* cleanup, error checking needed */
	sem_close(sem);
    sem_close(sem_sig);
	shmctl(shmid, IPC_RMID, 0);

	return 0;
}

