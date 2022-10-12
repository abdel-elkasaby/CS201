#include <stdio.h>
#include <stdlib.h>

#include "myutil.h"

int main(void) {

    int i = 5;

    printf("square: %d  cube: %d\n", squareit(i), cubeit(i));

    return EXIT_SUCCESS;
}