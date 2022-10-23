/* Omar Nassar
 * October 18, 2022
 * Portland State University CS201
 * Translate float to hex
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    int floatDouble = 0;
    char buf[BUFFER_SIZE] = {0};

    {
        int opt = 0;

        while ((opt = getopt(argc, argv, "fdH")) != -1) {
            switch(opt) {
            case 'f':
                floatDouble = 0;
                break;
            case 'd':
                floatDouble = 1;
                break;
            case 'H':
                printf("./float-2-hex [OPTION ...]\n");
                printf("\t-f   convert the input into floats for hex output (this is the default)\n");
                printf("\t-d   convert the input into doubles for hex output\n");
                printf("\t-H   display this help message and exit\n");
                exit(EXIT_SUCCESS);
                break;
            default:
                exit(EXIT_FAILURE);
            }
        }
    }

    while (fgets(buf, BUFFER_SIZE, stdin) != NULL) {
        char* remain;
        buf[strlen(buf) - 1] = '\0';
        if (floatDouble == 0) {
            float val = strtof(buf, &remain);
            printf("%-40s\t%.10e\t%.10f\t0x%08x\n", buf, val, val, *(unsigned int*) &val);
        }
        else if (floatDouble == 1) {
            double val = strtod(buf, &remain);
            printf("%-40s\t%.16le\t%.16lf\t0x%016lx\n", buf, val, val, *(long unsigned int*) &val);
        }
    }

    return EXIT_SUCCESS;
}