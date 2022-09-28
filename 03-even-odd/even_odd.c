#include <stdio.h>

// gcc -Wall -g even_odd.c -o even_odd
// ./even_odd

int main(void) {
    int value = 0;
#ifdef ICKY
    int even_odd = 0;

    do {
        printf("Enter a value (zero to terminate): ");
        scanf("%d", &value);
        even_odd = (value / 2) * 2;
        if (even_odd != value)
            printf("\t%d is odd\n", value);

        else printf("\t%d is even\n", value );

    } while (value != 0);
#endif //ICKY
#ifdef SHIFT
    int even_odd = 0;

    printf("Enter a value (zero to terminate): ");
    while ((scanf("%d", &value) > 0) && (value != 0)) {
        even_odd = value >> 1;
        even_odd <<= 1;

        if (even_odd != value)
            printf("\t%d is odd\n", value);

        else printf("\t%d is even\n", value );     
        printf("Enter a value (zero to terminate): ");   
    }
#endif //SHIFTY
    printf("Enter a value (zero to terminate): ");
    while ((scanf("%d", &value) > 0) && (value != 0)) {
        if ((value % 2) != 0) {
            printf("\t%d is odd\n", value);
        }
        else printf("\t%d is even\n", value );  
        printf("Enter a value (zero to terminate): ");
    }

    return 0;
}