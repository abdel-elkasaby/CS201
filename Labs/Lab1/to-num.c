/* Omar Nassar
 * October 13, 2022
 * Portland State University CS201
 * Displays ascii values of chars in octal, dec, and hex
 * Compilation Command: gcc -g -Wall -o to-num to-num.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_LEN 256

int main(void) {
    char str[STR_LEN] = {'\0'};
    fgets(str, STR_LEN, stdin);

    printf("octal output\n");
    for (int i = 0; i < strlen(str) - 1; i++) {
        printf("%04o ", (int) str[i]);
    }

    printf("\ndecimal output\n");
    for (int i = 0; i < strlen(str) - 1; i++) {
        printf("%d ", (int) str[i]);
    }

    printf("\nhex output\n");
    for (int i = 0; i < strlen(str) - 1; i++) {
        printf("0x%x ", (int) str[i]);
    }
    printf("\n");

    return EXIT_SUCCESS;
}