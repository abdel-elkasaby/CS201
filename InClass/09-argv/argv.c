#include <stdio.h>
#include <stdlib.h>

// gcc -Wall -g -o argv argv.c
// ./argv
// ./argv arg1 arg2 arg3 arg4
// ./argv *.c

int main(int argc, char *argv[]) {
    int i = 0;

    printf("The value of argc is: %d\n", argc);

    printf("The value of argv[0] is: %s\n\n", argv[0]);

    for(int i =1; i < argc; i++) {
        printf("\tThe value of argv[%d] is: %s\n", i, argv[i]);
    }

    printf("iterating by NULL value\n");
    for (i = 1; NULL != argv[i]; i++) {
        printf("\tThe value fo argv[%d] is: %s\n", i, argv[i]);
    }

    return EXIT_SUCCESS;
}