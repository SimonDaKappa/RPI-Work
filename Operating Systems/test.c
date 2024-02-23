#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(){
    fork();
    if (fork()) fork();
    fprintf(stderr, "hi\n");
}
