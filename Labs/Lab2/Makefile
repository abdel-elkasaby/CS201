# Omar Nassar
# October 18, 2022
# Portland State University CS201
# Makefile for float2hex and hex2float programs

CC = gcc
DEBUG = -g
DEFINES = 

CFLAGS = ${DEBUG} ${DEFINES} -Wall -Wshadow -Wunreachable-code -Wredundant-decls \
	-Wmissing-declarations -Wold-style-definition -Wmissing-prototypes \
	-Wdeclaration-after-statement -Wextra -Werror -Wpedantic

PROG1 = float-2-hex
PROG2 = hex-2-float

PROGS = ${PROG1} ${PROG2}

# $@ is the name of the target
# $^ is the names of all the prerequisites
# $< is the name of the first prerequisite

all: ${PROGS}

${PROG1}: ${PROG1}.o
	${CC} ${CFLAGS} -o $@ $^

${PROG1}.o: ${PROG1}.c
	${CC} ${CFLAGS} -c $<

${PROG2}: ${PROG2}.o
	${CC} ${CFLAGS} -o $@ $^ -lm

${PROG2}.o: ${PROG2}.c
	${CC} ${CFLAGS} -c $<

clean cls:
	-rm -f ${PROGS} *.o *~ \#*

tar:
	tar cvfz $(shell basename $(CURDIR)).tar.gz *.[ch] ?akefile
	@echo "\nVERIFICATION:\n"
	tar tvf $(shell basename $(CURDIR)).tar.gz

f2h: ${PROG1}

h2f: ${PROG2}