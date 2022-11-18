# Omar Nassar
# October 18, 2022
# Portland State University CS201
# Makefile for push_pop program

CC = gcc
DEBUG = -g
DEFINES = 

CFLAGS = ${DEBUG} ${DEFINES} ${OPTIONS}

TESTFLAGS = ${DEBUG} ${DEFINES} ${TESTOPTIONS}

OPTIONS = -Wall -Wshadow -Wunreachable-code -Wredundant-decls \
	-Wmissing-declarations -Wold-style-definition -Wmissing-prototypes \
	-Wdeclaration-after-statement -Wextra -Wpedantic -Werror

TESTOPTIONS = -Wall -Wshadow -Wunreachable-code -Wredundant-decls \
	-Wmissing-declarations -Wold-style-definition -Wmissing-prototypes \
	-Wdeclaration-after-statement -Wextra -Wpedantic

PROG1 = push_pop
PROG2 = stack_status

# $@ is the name of the target
# $^ is the names of all the prerequisites
# $< is the name of the first prerequisite

all: ${PROG1}

${PROG1}: ${PROG1}.o ${PROG2}.o
	${CC} ${CFLAGS} -o $@ $^

${PROG1}.o: ${PROG1}.c ${PROG1}.h
	${CC} ${CFLAGS} -c $<

${PROG2}.o: ${PROG2}.c ${PROG1}.h
	${CC} ${CFLAGS} -c $< 

test: ${PROG1}test

${PROG1}test: ${PROG1}test.o ${PROG2}test.o
	${CC} ${TESTFLAGS} -o $@ $^

${PROG1}test.o: ${PROG1}.c ${PROG1}.h
	${CC} ${TESTFLAGS} -c $< -o $@

${PROG2}test.o: ${PROG2}.c ${PROG1}.h
	${CC} ${TESTFLAGS} -c $< -o $@

clean cls:
	-rm -f ${PROG1} ${PROG1}test *.o *~ \#* 

tar:
	tar cvfz $(shell basename $(CURDIR)).tar.gz *.[ch] ?akefile
	@echo "\nVERIFICATION:\n"
	tar tvf $(shell basename $(CURDIR)).tar.gz