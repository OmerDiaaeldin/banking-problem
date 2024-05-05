#include<stdio.h>
#include<semaphore.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<unistd.h>
#define SHM_KEY 12345
#define SHM_SIZE 1024

int main(){
    sem_t *s1;
    s1 = sem_open("/first", O_CREAT, 0644, 0);
    // s2 = sem_open("/second", O_CREAT, 0644,0);
    sem_post(s1);
    int shmid;
    int key = SHM_KEY;
    char *shm;
    /* create shared memory segment */
    shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }
    /* attach shared memory segment */
    shm = shmat(shmid, NULL, 0);
    if (shm == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    sprintf(shm,"%d",100);

    sleep(50);
    sem_close(s1);
}