#include <stdio.h>
#include <ctype.h>

// gcc -Wall -g letters.c -o letters
// ./letters
// The quick brown fox jumps over the lazy dog

#define STR_LEN 256
#define NUM_LETTERS ('z' - 'a' + 1) // 26

int main(void) {
    char str[STR_LEN] = {'\0'};
    int counts[NUM_LETTERS] = {0};
    int ltr = 0;

    printf("Enter the string: ");
    fgets(str, STR_LEN, stdin);

    for (int i = 0; str[i] != '\0'; i++) {
        ltr = str[i];
        if (isalpha(ltr)) {
            ltr = toupper(ltr);
            ltr = ltr - 'A';
            counts[ltr]++;
        }
    }

    for (int i = 0; i < NUM_LETTERS; i++) {
        printf("The number of %c's is %d\n", (i+'A'), counts[i]);
    }
    

    return 0;
}