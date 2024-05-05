#include<stdio.h>
#include<semaphore.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<unistd.h>
#include<stdlib.h>
#define SHM_KEY 12345
#define SHM_SIZE 1024

void update(sem_t *s1, char *shm, int amount,int sleep_duration){
    sem_wait(s1);
    printf("Bank 3 change: %d\n", amount);
    int balance = atoi(shm);
    sprintf(shm,"%d",balance+amount);
    printf("New balance: %d\n",balance+amount);
    sleep(sleep_duration);
}

int main(){
    sem_t *s1;
    s1 = sem_open("/first", O_EXCL);

    int shmid;
    int key = SHM_KEY;
    char *shm;
    /* create shared memory segment */
    shmid = shmget(key, SHM_SIZE, 0666);
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

    int balance = atoi(shm);

    update(s1,shm,15,4);
    // sleep(2);

    update(s1,shm,45,2);
    sleep(3);

    update(s1,shm,65,3);
    sleep(1);
}