#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

// gcc -Wall -o ok_mult ok_mult.c
// ./ok_mult

int ok_mul_int(int, int, int *);
int ok_mul_short(short, short, short *);
int ok_mul_short2(short, short, short *);

int main(void) {

    {
        int x1 = 2147483;
        int x2 = 10;
        int prod = 0;
        int result = 0;

        result = ok_mul_int(x1, x2, &prod);
        printf("ok_mul_int\tx1: %d\tx2: %d\t\tprod: %d\t\tokay: %s\n"
                , x1, x2, prod, (result == 0) ? "yes" : "no");
        assert(result == 0);
    }

    {
        int x1 = INT_MAX;
        int x2 = 1000;
        int prod = 0;
        int result = 0;

        result = ok_mul_int(x1, x2, &prod);
        printf("ok_mul_int\tx1: %d\tx2: %d\tprod: %d\t\tokay: %s\n"
                , x1, x2, prod, (result == 0) ? "yes" : "no");
        assert(result == 1);
    }
    
    {
        short x1 = 2000;
        short x2 = 10;
        short prod = 0;
        int result = 0;

        result = ok_mul_short(x1, x2, &prod);
        printf("ok_mul_short\tx1: %hd\tx2: %hd\t\tprod: %hd\t\tokay: %s\n"
                , x1, x2, prod, (result == 0) ? "yes" : "no");
        assert(result == 0);
    }

    {
        short x1 = SHRT_MAX;
        short x2 = 1000;
        short prod = 0;
        int result = 0;

        result = ok_mul_short(x1, x2, &prod);
        printf("ok_mul_short\tx1: %hd\tx2: %hd\tprod: %hd\t\tokay: %s\n"
                , x1, x2, prod, (result == 0) ? "yes" : "no");
        //assert(result == 1);
    }
    
    {
        short x1 = 2000;
        short x2 = 10;
        short prod = 0;
        int result = 0;

        result = ok_mul_short2(x1, x2, &prod);
        printf("ok_mul_short2\tx1: %hd\tx2: %hd\t\tprod: %hd\t\tokay: %s\n"
                , x1, x2, prod, (result == 0) ? "yes" : "no");
        assert(result == 0);
    }

    {
        short x1 = SHRT_MAX;
        short x2 = 1000;
        short prod = 0;
        int result = 0;

        result = ok_mul_short2(x1, x2, &prod);
        printf("ok_mul_short2\tx1: %hd\tx2: %hd\tprod: %hd\t\tokay: %s\n"
                , x1, x2, prod, (result == 0) ? "yes" : "no");
        assert(result == 1);
    }

    return EXIT_SUCCESS;
}

int ok_mul_int(int x, int y, int *dest) {
    int result;

    *dest = x * y;

    asm("seto %%bl;"
        "movzbl %%bl, %0;"
        : "=r" (result)
        :
        : "%ebx"
    );

    return result;
}

int ok_mul_short(short x, short y, short *dest) {
    int result;

    *dest = x * y;

    asm("seto %%bl;"
        "movzbl %%bl, %0;"
        : "=r" (result)
        :
        : "%ebx"
    );

    return result;
}

int ok_mul_short2(short x, short y, short *dest) {
    int result;

    asm("movw %2, %%ax;"
        "imulw %3;"
        "movw %%ax, %0;"
        "seto %%dl;"
        "movzb %%dl, %1;"
        : "=r" (*dest), "=r" (result)
        : "r" (x), "r" (y)
        : "%ax", "%dx"
    );

    return result;
}