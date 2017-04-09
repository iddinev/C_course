#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define SHM_SIZE 100
#define SEM_NAME "shm"
#define SEM_SIG_NAME "shm_sig"
#define FTOK_FILE "shm_server"

int main() {
	int shmid, i;
	key_t key;
	char *data;
	sem_t *sem;
	sem_t *sem_sig;
	char message[100]="This is server speaking through shared memory..."; 

	/* create and initialize semaphores */
	sem = sem_open(SEM_NAME, O_CREAT, 0644, 1);
	if (sem == SEM_FAILED) {
		perror("semopen()");
		sem_unlink(SEM_NAME);
		return 1;
    }
	sem_sig = sem_open(SEM_SIG_NAME, O_CREAT, 0644, 0);
	if (sem == SEM_FAILED) {
		perror("semopen()");
		sem_unlink(SEM_SIG_NAME);
		return 1;
	}

	/* create key for shared memeory */
        key = ftok(FTOK_FILE, 33);

	/* create shared memory segment with this key */
	shmid = shmget(key, SHM_SIZE, IPC_CREAT|0666);
	if (shmid == -1) {
		perror("shmget()");
		return 1;
	}

	/* map this segment to the virtual memory */
	data = shmat(shmid, NULL, 0);

	/* start writing into memory */
	i = 0;
	do {
		sem_wait(sem);
		data[i] = message[i];
		sem_post(sem);
	} while (message[i++] != 0);

	/* wait for the client to indicate completion */
    sem_wait(sem_sig);
	/* while(*data != '#') { */
		/* sleep(1); */
	/* } */

	/* cleanup, more error checking should be done here ;) */
	sem_close(sem);
	sem_unlink(SEM_NAME);
	sem_close(sem_sig);
	sem_unlink(SEM_SIG_NAME);
	shmctl(shmid, IPC_RMID, 0);

	return 0;
}
