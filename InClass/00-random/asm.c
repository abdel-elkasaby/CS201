#include <stdio.h>
#include <stdlib.h>

int main (void) {
    int x = 2;
    int y = 3;

    int result; 

    asm("movl %1, %%ebx;"
        "movl %2, %%ecx;"
        "sall %%cl, %%ebx;"
        "movl %%ebx, %0"
        : "=r" (result)
        : "r" (x), "r" (y)
        : "%eax", "%edx"
    );

    printf("%d\n", result);

    return EXIT_SUCCESS;
}