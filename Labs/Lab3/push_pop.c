/* Omar Nassar
 * November 11, 2022
 * Portland State University CS201
 * Manipulating stack using push and pop instructions
 * A portion of this code was written by the instructor Jesse Chaney
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <assert.h>

#include "push_pop.h"

// The valid commands:
//   status
//   push %reg
//   push $val
//   pop %reg

int is_verbose = 0;
static unsigned long stack_bot = DEF_STACK_BOT; // the high address for the stack
static unsigned long stack_limit = DEF_STACK_LIMIT; // the low address for the stack
static unsigned long rsp = DEF_RSP; // the initial value for the rsp register
static unsigned long *stack = NULL; // points to the bytes for the stack
static unsigned long registers[REG_RDX + 1] = { // the general purpose registers
    REG_RAX + 20,
    REG_RBX + 30,
    REG_RCX + 40,
    REG_RDX + 50
};

static void pop(char *);
static void push_reg(char *);
static void push_value(char *);

static void pop(char *reg) {
    //#error stuff goes in here
}

static void push_reg(char *reg) {
    //#error stuff goes in here
}

static void push_value(char *reg) {
    //#error stuff goes in here
}

int main(int argc, char *argv[]) {
    FILE *ifile = stdin;
    FILE *ofile = stdout;

    {
        int opt = 0;
        int res_count = 0;

        while ((opt = getopt(argc, argv, GETOPT_STRING)) != -1) {
            switch (opt) {
            case 'i':
                ifile = fopen(optarg, "r");
                if (!ifile) {
                    perror("failed to open file");
                    return(EXIT_FAILURE);
                }
                break;
            case 'o':
                ofile = fopen(optarg, "r");
                    if (!ofile) {
                        perror("failed to open file");
                        return(EXIT_FAILURE);
                    }
                break;
            case 'h':
                printf("%s\n\toptions: %s\n", argv[0], GETOPT_STRING);
                printf("\ti: name of input file\n");
                printf("\to: name of output file\n");
                printf("\tb: stack_bottom (high address, as hex)\n");
                printf("\tl: stack limit (low address, as hex)\n");
                printf("\ts: beginning %%rsp value (within the stack, as hex)\n");
                printf("\tv  verbose output\n");
                printf("\th  help\n");

                exit(EXIT_SUCCESS);
                break;
            default:
                break;
            }
        }
    }

    //#error lots of stuff goes in here
    
    return EXIT_SUCCESS;
}
