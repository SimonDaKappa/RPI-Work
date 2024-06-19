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

int main(int argc, char** argv){
    key_t key = SHM_KEY;
    int shmid = shmget(key, 1024, IPC_CREAT | 0666); // 0666 is read/write access granted
    if(shmid < 0){
        perror("shmget");
        exit(1);
    }
    unsigned long* data = shmat(shmid, NULL, 0);
    if(data == (unsigned long*)-1){
        perror("shmat");
        exit(1);
    }

    shmat(shmid, data, 0);

    // Call Exam2_q5_process2.c
    char* args[] = {"./Exam2_q5_process2", NULL};
    execvp(args[0], args);

    if (argv[2] == "-RM_SHM"){
        // Call RHMS_HM.c to print the shared memory
        char* args[] = {"./RM_SHM", NULL};
        execvp(args[0], args);
    }

    shmdt(data);
    shmctl(shmid, IPC_RMID, NULL);
}
