CC = gcc
DEBUG = -g
DEFINES = -DARRAY -DREUSE

CFLAGS = ${DEBUG} -Wall -Wshadow -Wunreachable-code -Wredundant-decls \
	-Wmissing-declarations -Wold-style-definition -Wmissing-prototypes \
	-Wdeclaration-after-statement -Wextra -Werror -Wpedantic ${DEFINES}

PROG1 = str_tests
PROGS = ${PROG1}
STR_FUN = str_functions

# $@ is the name of the target
# $< is the name of the first prerequisite
# $^ is the names of all the prerequisites

all: ${PROGS}

${PROG1}: ${PROG1}.o ${STR_FUN}.o
	${CC} ${CFLAGS} -o $@ $^

${PROG1}.o: ${PROG1}.c Makefile
	${CC} ${CFLAGS} -c $<

${STR_FUN}.o: ${STR_FUN}.c Makefile
	${CC} ${CFLAGS} -c $<

clean cls:
	rm -f ${PROGS} *.[o] *~ \#*

git gat get:
#	if [! -d .git] ; then git init; fi
	git add *.[ch] ?akefile
	git commit -m "my lazy git commit comment"

tar:
	tar cvfz $(shell basename $(CURDIR)).tar.gz *.[ch] ?akefile
	@echo "\nVERIFICATION:\n"
	tar tvf $(shell basename $(CURDIR)).tar.gz

