#include <stdio.h>

// gcc -Wall -g tupper.c -o tupper
// ./tupper

#define STR_LEN 256

int main(void) {
    char str[STR_LEN] = {'\0'};

    printf("Enter the string: ");
    //scanf("%s", str);
    fgets(str, STR_LEN, stdin);

    for (int i = 0; str[i] != '\0'; i++) {
        /*if ((str[i] >= 97) && (str[i] <= 122)) {
            str[i] -= 32;
        }*/

        if ((str[i] >= 'a') && (str[i] <= 'z')) {
            str[i] -= ('a' - 'A');
        }
    }

    printf("upper case version: %s\n", str);    

    return 0;
}