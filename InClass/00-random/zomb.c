#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sig_handler(int signo);

int main(void) {
    signal(SIGINT, sig_handler);
    pid_t child1 = 0;
    pid_t child2 = 0;
    pid_t child3 = 0;

    if (child1 = fork() == 0) exit(1);
    if (child2 = fork() == 0) exit(1);
    if (child3 = fork() == 0) exit(1);

    while(1) {}

    return EXIT_SUCCESS;
}

void sig_handler(int signo) {
    exit(EXIT_SUCCESS);
}