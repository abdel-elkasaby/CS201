/* Omar Nassar
 * October 18, 2022
 * Portland State University CS201
 * Translate hex to float
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    FILE *file = stdin;
    char *filename = NULL;
    char buf[BUFFER_SIZE] = {0};

    int numbits = 32;
    int fracbits = 23;
    int fracadd = 1;
    int expbits = 8;
    int expbias = 127;
    int verbose = 0;
    int biasChanged = 0;

    {
        int opt = 0;

        while ((opt = getopt(argc, argv, "i:dhbme:E:f:F:vH")) != -1) {
            switch(opt) {
            case 'i':
                file = fopen(optarg, "r");
                filename = optarg;
                if (file == NULL) {
                    perror("failed to open file");
                    fprintf(stderr, "could not open input file %s\n", filename);
                    return(EXIT_FAILURE);
                }
                break;
            case 'd':
                numbits = 64;
                fracbits = 52;
                fracadd = 1;
                expbits = 11;
                expbias = 1023;
                break;
            case 'h':
                numbits = 16;
                fracbits = 10;
                fracadd = 1;
                expbits = 5;
                expbias = 15;
                break;
            case 'b':
                numbits = 16;
                fracbits = 7;
                fracadd = 1;
                expbits = 8;
                expbias = 127;
                break;
            case 'm':
                numbits = 8;
                fracbits = 3;
                fracadd = 1;
                expbits = 4;
                expbias = -2;
                break;
            case 'e':
                expbits = strtol(optarg, NULL, 10);
                numbits = expbits + fracbits + 1;
                if (!biasChanged) expbias = ((int) pow(2, expbits - 1)) - 1;
                break;
            case 'E':
                expbias = strtol(optarg, NULL, 10);
                biasChanged = 1;
                break;
            case 'v':
                verbose = 1;
                break;
            case 'f':
                fracbits = strtol(optarg, NULL, 10);
                numbits = expbits + fracbits + 1;
                break;
            case 'F':
                fracadd = strtol(optarg, NULL, 10);
                break;
            case 'H':
                printf("Usage: ./hex-2-float [OPTION ...]\n");
                printf("\t-i <file_name> specify the name of the input file (defaults to stdin)\n");
                printf("\t     Settings default to single precision (float, 32-bits, 1-8-23)\n");
                printf("\t-d   use settings for double precision (double, 64-bits, 1-11-52)\n");
                printf("\t-h   use settings for half precision (_Float16, 16-bits, 1-5-10)\n");
                printf("\t-b   use settings for half precision (bfloat16, 16-bits, 1-8-7)\n");
                printf("\t-m   use settings for quarter precision (minifloat, 8-bits, 1-4-3  bias -2)\n");
                printf("\t-e # set the number of bits to use for the exponent\n");
                printf("\t-E # set the value used for the exponent bias\n");
                printf("\t-f # set the number of bits to use for the fraction\n");
                printf("\t-F # set the value to add to the fraction (unstored fraction bits)\n");
                printf("\t-v   display the settings (to stderr) before reading input\n");
                printf("\t-H   display this help message and exit\n");
                
                exit(EXIT_SUCCESS);
                break;
            default:
                exit(EXIT_FAILURE);
            }
        }
    }

    if (verbose) {
        if (filename == NULL) fprintf(stderr, "\tinput file\t: %s\n", "stdin");
        else fprintf(stderr, "\tinput file\t: %s\n", filename);
        fprintf(stderr, "\tnumber of bits\t: %d\n", numbits);
        fprintf(stderr, "\tfraction bits\t: %d\n", fracbits);
        fprintf(stderr, "\tfraction add\t: %d\n", fracadd);
        fprintf(stderr, "\texponent bits\t: %d\n", expbits);
        fprintf(stderr, "\texponent bias\t: %d\n", expbias);
        fprintf(stderr, "\tverbose\t\t: yes\n\n");
    }

    

    while(fgets(buf, BUFFER_SIZE, file) != NULL) {
        //unsigned long val = strtol(buf, NULL, 16);
        unsigned long val = 0;
        unsigned long exp = 0;
        unsigned long signMask = 0x1l << (fracbits + expbits);
        unsigned long fracMask = 0x1l << (fracbits - 1);
        unsigned long pMask = 0x1l << (fracbits + expbits);
        unsigned long expMask = 0x1l;
        char *sign;
        unsigned long exp2 = 0;
        int newexp = 0;
        double frac = 0;
        int currexp = -1;
        double value = 0;
        sscanf(buf, "%lx", &val);
        
        for (int i = 0; i < expbits - 1; i++) {
            expMask <<= 1;
            expMask |= 0x1;
        }
        expMask <<= fracbits;
        exp = val & expMask;

        exp2 = exp >> fracbits;
        newexp = (int) exp2 - expbias;

        printf("%s", buf);
        printf("\t%d ", (val & pMask) ? 1 : 0);
        for (int i = expbits; i > 0; i--) {
            pMask >>= 1;
            printf("%d", (val & pMask) ? 1 : 0);
        }
        printf(" ");
        for (int i = fracbits; i > 0; i--) {
            pMask >>= 1;
            printf("%d", (val & pMask) ? 1 : 0);
        }

        for (int i = 0; i < fracbits; i++) {
            if (val & fracMask) frac += pow(2, currexp);
            currexp--;
            fracMask >>= 1;
        }

        //printing s e f under float
        printf("\n\ts ");
        for (int i = 0; i < expbits; i++) printf("e");
        printf(" ");
        for (int i = 0; i < fracbits; i++) printf("f");
        printf("\n");

        if (exp == 0) {
            printf("\tdenormalized value\n");
            newexp = 1 - expbias;
        }
        else if (exp == expMask) {
            if (frac == 0) {
                if ((signMask & val) == 0) printf("\tpositive infinity\n\n");
                else printf("\tnegative infinity\n\n");
            }
            else {
                printf("\tNaN\n\n");
            }
            continue;
        }
        else frac = frac + fracadd;

        value = frac * pow(2, newexp);

        if ((signMask & val) == 0) sign = "positive";
        else {
            sign = "negative";
            value *= -1;
        }
        printf("\tsign:\t\t%s\n", sign);
        printf("\texponent:\t%-10d\n", newexp);
        printf("\tfraction:\t%0.20f\n", frac);
        printf("\tvalue:\t\t%0.20f\n", value);
        printf("\tvalue:\t\t%0.20e\n\n", value);
        
    }

    if (file != stdin) fclose(file);

    return EXIT_SUCCESS;
}