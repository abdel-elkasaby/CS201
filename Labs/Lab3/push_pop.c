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
int rows = 0;
FILE *ofile = NULL;
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
static int checkReg(char *);

int main(int argc, char *argv[]) {
    FILE *ifile = stdin;
    char buf[BUFFER_SIZE] = {0};
    long bytes;
    ofile = stdout;
    
    {
        int opt = 0;
        //int res_count = 0;

        while ((opt = getopt(argc, argv, GETOPT_STRING)) != -1) {
            switch (opt) {
            case 'i':
                ifile = fopen(optarg, "r");
                if (!ifile) {
                    perror("failed to open file");
                    return EXIT_FAILURE;
                }
                if (is_verbose) fprintf(stderr, "input file: %s\n", optarg);
                break;
            case 'o':
                ofile = fopen(optarg, "w");
                if (!ofile) {
                    perror("failed to open file");
                    return EXIT_FAILURE;
                }
                if (is_verbose) fprintf(stderr, "output file: %s\n", optarg);
                break;
            case 'b':
                stack_bot = strtol(optarg, NULL, 16);
                break;
            case 'l':
                stack_limit = strtol(optarg, NULL, 16);
                break;
            case 's':
                rsp = strtol(optarg, NULL, 16);
                break;
            case 'v':
                is_verbose = 1;
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

    if (stack_bot <= stack_limit) {
        fprintf(stderr, "stack botton must be higher than stack limit\n");
        return EXIT_FAILURE;
    }
    else if (stack_limit % 8) {
        fprintf(stderr, "stack_limit value must be a multiple of 8\n");
        return EXIT_FAILURE;
    }
    if (rsp > stack_bot || rsp < stack_limit) {
        fprintf(stderr, "initial rsp value outside of stack\n");
        return EXIT_FAILURE;
    }
    else if (stack_bot % 8) {
        fprintf(stderr, "stack_bot value must be a multiple of 8\n");
        return EXIT_FAILURE;
    }
    else if (rsp % 8) {
        fprintf(stderr, "initial rsp value must be a multiple of 8\n");
        return EXIT_FAILURE;
    }



    bytes = stack_bot - stack_limit + 0x8;
    rows = bytes/8;

    stack = (unsigned long *) calloc(rows, REG_SIZE);

    if (is_verbose) fprintf(ofile, ">> allocating stack: %ld bytes %d rows\n", bytes, rows);

    //NOTE TO SELF: MUST CHANGE ALL PRINTF TO FPRINTF
    while(fgets(buf, BUFFER_SIZE, ifile)) {
        char *remain = buf;
        char *reg;
        // int option = 0; //1 for status, 2 for push, 3 for pop

        remain = strtok(remain, WHITESPACE);
        if (!remain) continue;
        //printf("PARSED: %s OPTION: %d\n", remain, option);
        if (strcmp(remain, CMD_STATUS) == 0) {
            stack_status(stack, registers, rsp, stack_bot, stack_limit);
        }
        else if (strcmp(remain, CMD_PUSH) == 0) {
            // printf("PUSH\n");
            remain = strtok(NULL, WHITESPACE);
            if (!remain) continue;
            if (remain[0] == '$') {
                char *check;
                // printf("value mode\n");
                reg = remain + 1;
                strtoul(reg, &check, 16);
                if (check == reg) fprintf(ofile, "cannot parse number\n");
                else push_value(reg);
                // printf("new string: %s\n", reg);
            }
            else if (remain[0] == '%') {
                // printf("register mode\n");
                reg = remain + 1;
                // printf("new string: %s\n", reg);
                if (is_verbose) fprintf(stderr, ">> push reg: 0x%04lx %%%s\n", rsp, reg);
                if (!checkReg(reg)) fprintf(ofile, "unrecognized register: %%%s\n", reg);
                else push_reg(reg);
            }
            else {
                fprintf(ofile, "unrecognized operand for push: %s\n", remain);
                continue;
            }
        }
        else if (strcmp(remain, CMD_POP) == 0) {
            // printf("POP\n");
            remain = strtok(NULL, WHITESPACE);
            if (!remain) continue;
            if (remain[0] == '%') {
                // printf("register\n");
                reg = remain + 1;
                // printf("new string: %s\n", reg);
                if (is_verbose) fprintf(stderr, ">> pop: 0x%04lx %%%s\n", rsp, reg);
                if (!checkReg(reg)) fprintf(ofile, "unrecognized register: %%%s\n", reg);
                else pop(reg);
            }
            else {
                fprintf(ofile, "unrecognized operand for pop: %s\n", remain);
                continue;
            }
        }
        else printf("command not recognized: %s\n", remain);
    }
    
    if (ifile != stdin) fclose(ifile);
    if (ofile != stdout) fclose(ofile);
    if (stack) free(stack);
    
    return EXIT_SUCCESS;
}

static void pop(char *reg) {
    int regNum = checkReg(reg) - 1;
    if (rsp == stack_bot) {
        fprintf(ofile, "at bottom of stack\n");
        return;
    }

    //printf("RSP: %08lx RSP-STACK_LIM: %08lx\n", rsp, rsp - stack_limit);
    registers[regNum] = stack[rows - ((rsp - stack_limit)/8 + 1)];
    rsp += 0x8;
    //printf("ROW OF RSP: 0x%08lx VAL OF STACK: 0x%08lx\n", rsp, stack[(rsp - stack_limit)/0x8]);
    return;    
}

static void push_reg(char *reg) {
    int regNum = checkReg(reg) - 1;

    if (rsp == stack_limit) {
        fprintf(ofile, "overflow of stack\n");
        return;
    }
    rsp -= 0x8;
    stack[rows - ((rsp - stack_limit)/8 + 1)] = registers[regNum];

    

    return;
}

static void push_value(char *reg) {
    unsigned long val = strtoul(reg, NULL, 16);
    
    if (is_verbose) fprintf(stderr, ">> push val: 0x%04lx 0x%04ld\n", rsp, val);

    if (rsp == stack_limit) {
        fprintf(ofile, "overflow of stack\n");
        return;
    }

    rsp -= 0x8;
    stack[rows - ((rsp - stack_limit)/8 + 1)] = val;

    if (is_verbose) fprintf(stderr, "  >> push: new rsp 0x%04lx\n", rsp);
    return;
}

static int checkReg(char *reg) {
    if (strcmp(reg, RAX) == 0) return 1;
    else if (strcmp(reg, RBX) == 0) return 2;
    else if (strcmp(reg, RCX) == 0) return 3;
    else if (strcmp(reg, RDX) == 0) return 4;
    
    return 0;
}