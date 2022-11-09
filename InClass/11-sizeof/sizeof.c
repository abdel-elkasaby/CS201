#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <values.h>

// gcc -Wall -g -o sizeof sizeof.c
// ./sizeof

int main (void) {
    {
        unsigned int endian = 1;
        char *ecp = (char *) &endian;

        if (ecp[0] == '\0') printf("This is a big endian architecture\n");
        else printf("This is a little endian architecture\n");
    }
    {
        unsigned int endian = 0x006C694C;
        char *ecp = (char *) &endian;

        if (strcmp(ecp, "Lil") == 0) printf("This is a little endian architecture\n");
        else printf("This is a big endian architecture\n");
    }

    printf("Size of basic C data types\n");
    printf("\t\t\t\tbytes\t\tbits\n");
    printf("\tsizeof(char)\t\t%3zd\t\t%3zd\n", sizeof(char), CHARBITS);
    printf("\tsizeof(short)\t\t%3zd\t\t%3zd\n", sizeof(short), SHORTBITS);
    printf("\tsizeof(int)\t\t%3zd\t\t%3zd\n", sizeof(int), INTBITS);
    printf("\tsizeof(long)\t\t%3zd\t\t%3zd\n", sizeof(long), LONGBITS);

    printf("\tsizeof(float)\t\t%3zd\t\t%3zd\n", sizeof(float), sizeof(float) * CHARBITS);
    printf("\tsizeof(double)\t\t%3zd\t\t%3zd\n", sizeof(double), sizeof(double) * CHARBITS);
    printf("\tsizeof(long double)\t%3zd\t\t%3zd\n", sizeof(long double), sizeof(long double) * CHARBITS);
    printf("\tsizeof(void *)\t\t%3zd\t\t%3zd (aka, a pointer)\n", sizeof(void *), sizeof(void *) * CHARBITS);

    printf("\n");
    {
        char ch[50] = {0};
        char *ch_ptr = ch;

        printf("\tsizeof(ch)\t\t%3zd\n", sizeof(ch));
        printf("\tsizeof(ch_ptr)\t\t%3zd\n", sizeof(ch_ptr));
    }

    printf("\n");
    {
        int i[50] = {0};
        int *i_ptr = i;

        printf("\tsizeof(i)\t\t%3zd\n", sizeof(i));
        printf("\tsizeof(i_ptr)\t\t%3zd\n", sizeof(i_ptr));
        printf("\tsizeof(i[0])\t\t%3zd\n", sizeof(i[0]));
    }

    printf("\n");
    {
        typedef struct account_s {
            int account_number;
            double balance;
            char name[53];
        } account_t;

        struct account_s a_s;
        account_t a_t;
        account_t *a_ptr = &a_s;

        printf("\tsizeof(struct account_s)\t%3zd\n", sizeof(struct account_s));
        printf("\tsizeof(account_t)\t\t%3zd\n", sizeof(account_t));
        printf("\tsizeof(a_s)\t\t\t%3zd\n", sizeof(a_s));
        printf("\tsizeof(a_t)\t\t\t%3zd\n", sizeof(a_t));
        printf("\tsizeof(a_t.balance)\t\t%3zd\n", sizeof(a_t.balance));
        printf("\tsizeof(a_ptr)\t\t\t%3zd\n", sizeof(a_ptr));
    }

    return EXIT_SUCCESS;
}