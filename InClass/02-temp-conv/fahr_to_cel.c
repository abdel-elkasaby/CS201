#include <stdio.h>

// gcc -Wall -g fahr_to_cel.c -o fahr_to_cel
// ./fahr_to_cel

/*
Fahrenheit Celsius
32          0.0000
40          4.4444
50         10.0000
60         15.5556
100        37.777
212       100.0000
*/

int main (void) {
    
#ifdef WRONG
    int fahrenheit = 0;
    int celsius = 0;

    printf("Enter temperature in Fahrenheit: ");
    scanf("%d", &fahrenheit);

    celsius = (fahrenheit - 32) * 5 / 9;
    printf("\nCelsius = %d\n", celsius);
#else //WRONG
    float fahrenheit = 0.0;
    float celsius = 0.0;

    printf("Enter temperature in Fahrenheit: ");
    scanf("%f", &fahrenheit);

    celsius = (fahrenheit - 32.0) * 5.0 / 9.0;

    printf("\nCelsius = %.4f\n", celsius);
#endif //WRONG
    return 0;
}