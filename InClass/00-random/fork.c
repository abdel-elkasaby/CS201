#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    pid_t child1 = 0;// = fork();
    pid_t child2 = 0;//= fork();
    
    int child1status;
    int child2status;

    if ((child1 = fork()) == 0) {
        printf("Child1 PID: %d\n", getpid());
        printf("Parent PID: %d\n", getppid());
        exit(3);
    }

    if ((child2 = fork()) == 0) {
        printf("Child2 PID: %d\n", getpid());
        printf("Parent PID: %d\n", getppid());
        exit(3);
    }

    waitpid(child1, &child1status, 0);
    waitpid(child2, &child2status, 0);
    
    if (WIFEXITED(child1status) && WIFEXITED(child2status)) {

        printf("\n\nParent PID: %d\n", getpid());
        printf("Child1 PID: %d\n", child1);
        printf("Child2 PID: %d\n", child2);
    }

    return EXIT_SUCCESS;
}