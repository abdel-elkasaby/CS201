/* Omar Nassar
 * October 13, 2022
 * Portland State University CS201
 * Translates octal, binary, or hex to ascii
 * Compilation Command: gcc -g -Wall -o to-char to-char.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_LEN 256

int main(void) {
    int option = 0;
    char str[STR_LEN] = {'\0'};

    scanf("%d", &option);
    getchar(); //getting rid of buffer



    if (option == 10) printf("decimal input\n");
    else if (option == 8) printf("octal input\n");
    else if (option == 16) printf("hex input\n");
    else {
        printf("Invalid Option Selected.\n");
        return EXIT_FAILURE;
    }

    fgets(str, STR_LEN, stdin);

    char *remain = str;
    while (strcmp(remain, " 00\n") != 0) {
        int val = strtol(remain, &remain, option);
        printf("%c", (char) val);
    }    

    printf("\n");
    return EXIT_SUCCESS;
}