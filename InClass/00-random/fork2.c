#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fork3(void);

int main(void) {
    pid_t child = 0;// = fork();

    if ((child = fork()) == 0) {
        printf("Child PID: %d\n", getpid());
        printf("Parent PID: %d\n", getppid());
        exit(1);
    }
    
    else {
        wait(NULL);
        printf("\n\nParent PID: %d\n", getpid());
        printf("Child PID: %d\n", child);
    }

    printf("\n\n");
    fork3();

    return EXIT_SUCCESS;
}

void fork3(void) {
    printf("L0\n");
    fork();
    printf("L1\n");
    fork();
    printf("L2\n");
    fork();
    printf("Bye\n");
}

