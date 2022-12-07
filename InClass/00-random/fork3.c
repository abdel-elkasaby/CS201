#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int i;
    for (i = 0; i < 2; i++) {
        fork();
    }
    printf("hello!\n");
    return 0;
}