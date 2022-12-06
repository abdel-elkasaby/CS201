#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    pid_t child = 0;
    child = fork();
    if (child) while(1) {}
    wait(NULL);
    return 0;
}