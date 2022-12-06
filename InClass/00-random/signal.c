#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sig_handler(int signo);

int count = 5;

int main(void) {
    signal(SIGINT, sig_handler);
    while (1) {}
    return EXIT_SUCCESS;
}

void sig_handler(int signo) {
    if (count == 0) exit(EXIT_SUCCESS);
    printf("Ha ha\n");
    count--;
}