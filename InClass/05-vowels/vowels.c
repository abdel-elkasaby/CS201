#include <stdio.h>

// gcc -Wall -g vowels.c -o vowels
// ./vowels
// The quick brown fox jumps over the lazy dog

#define STR_LEN 256

enum vowels{A_COUNT, E_COUNT, I_COUNT, O_COUNT, U_COUNT, Y_COUNT};

int main(void) {

    char str[STR_LEN] = {'\0'};
    int counts[Y_COUNT + 1] = {0};

    printf("Enter the string: ");
    fgets(str, STR_LEN, stdin);
    for(int i = 0; str[i] != '\0'; i++) {
        switch (str[i]) {
            case 'a':
            case 'A':
                counts[A_COUNT]++;
                break;
            case 'e':
            case 'E':
                counts[E_COUNT]++;
                break;
            case 'i':
            case 'I':
                counts[I_COUNT]++;
                break;
            case 'o':
            case 'O':
                counts[O_COUNT]++;
                break;
            case 'u':
            case 'U':
                counts[U_COUNT]++;
                break;
            case 'y':
            case 'Y':
                counts[Y_COUNT]++;
                break;
            default:
                break;
        }
    }
    printf("The number of A's is %d\n", counts[A_COUNT]);
    printf("The number of E's is %d\n", counts[E_COUNT]);
    printf("The number of I's is %d\n", counts[I_COUNT]);
    printf("The number of O's is %d\n", counts[O_COUNT]);
    printf("The number of U's is %d\n", counts[U_COUNT]);
    printf("The number of Y's is %d\n", counts[Y_COUNT]);

    return 0;
}