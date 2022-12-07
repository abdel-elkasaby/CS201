#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
    for (int i = 0; i < argc; i++) {
        printf("argv[%d]: %s\n", i, argv[i]);
    }
    printf("%-15s\n", "abcdfasdfasdfasdfadsfasds");
    return EXIT_SUCCESS;
}