#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_KEY 8192

int main(){
    key_t key = SHM_KEY;
    int shmid = shmget(key, 1024, IPC_CREAT | 0666); // 0666 is read/write access granted

    if(shmid < 0){
        perror("shmget");
        exit(1);
    }

    unsigned long* data = shmat(shmid, NULL, 0);
    // print the fibonacci sequence

    for(int i = 0; i < 1024 / sizeof(unsigned long); i++){
        printf("%lu\n", data[i]);
    }
    shmdt(data);
}