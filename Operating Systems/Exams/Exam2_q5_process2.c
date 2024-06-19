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

int main(int argc, char **argv)
{
    key_t key = SHM_KEY;
    int shmid = shmget(key, 1024, IPC_CREAT | 0666); // 0666 is read/write access granted
    if (shmid < 0)
    {
        perror("shmget");
        exit(1);
    }

    unsigned long *data = shmat(shmid, NULL, 0);

    // Compute the fibonacci sequence and store it in the shared memory until overflow
    data[0] = 0;
    data[1] = 1;
    int i = 2;
    while (1)
    {
        data[i] = data[i - 1] + data[i - 2];
        if (data[i] < data[i - 1])
        {
            break;
        }
        i++;
    }

    // detach the shared memory
    shmdt(data);
    return 0;
}   