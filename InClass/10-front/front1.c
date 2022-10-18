#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

// ./front1 < front1.c

#define BUFFER_SIZE 1024
#define MAX_LINES 5

int main(int argc, char *argv[]) {
    FILE *ifile = stdin;
    int line_count = 0;
    int max_lines = MAX_LINES;
    char buf[BUFFER_SIZE] = {0};

#ifdef BASIC
    char *buf_ptr = NULL;

    buf_ptr = fgets(buf, BUFFER_SIZE, ifile);
    line_count++;
    while (line_count <= max_lines && buf_ptr != NULL) {
        printf("%s", buf);
        buf_ptr = fgets(buf, BUFFER_SIZE, ifile);
        line_count++;
    }
#else //BASIC
    while ((line_count++ < max_lines) && fgets(buf, BUFFER_SIZE, ifile) != NULL) {
        printf("%s", buf);
    }
#endif //BASIC

    return EXIT_SUCCESS;
}