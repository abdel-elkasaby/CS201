CC = gcc
DEBUG = -g
DEFINES = 

CFLAGS = ${DEBUG} ${DEFINES} -Wall -Wshadow -Wunreachable-code -Wredundant-decls \
	-Wmissing-declarations -Wold-style-definition -Wmissing-prototypes \
	-Wdeclaration-after-statement -Werror 

PROG1 = front1
PROG2 = front2
PROG3 = front3
PROG4 = front4

PROGS = ${PROG1} ${PROG2} ${PROG3} ${PROG4}

# $@ is the name of the target
# $^ is the names of all the prerequisites
# $< is the name of the first prerequisite

all: ${PROGS}

${PROG1}: ${PROG1}.o
	${CC} ${CFLAGS} -o $@ $^

${PROG1}.o: ${PROG1}.c
	${CC} ${CFLAGS} -c $<

${PROG2}: ${PROG2}.o
	${CC} ${CFLAGS} -o $@ $^

${PROG2}.o: ${PROG2}.c
	${CC} ${CFLAGS} -c $<

${PROG3}: ${PROG3}.o
	${CC} ${CFLAGS} -o $@ $^

${PROG3}.o: ${PROG3}.c
	${CC} ${CFLAGS} -c $<

${PROG4}: ${PROG4}.o
	${CC} ${CFLAGS} -o $@ $^

${PROG4}.o: ${PROG4}.c
	${CC} ${CFLAGS} -c $<


clean cls:
	-rm -f ${PROGS} *.o *~ \#*

tar:
	tar cvfz $(shell basename $(CURDIR)).tar.gz *.[ch] ?akefile
	@echo "\nVERIFICATION:\n"
	tar tvf $(shell basename $(CURDIR)).tar.gz