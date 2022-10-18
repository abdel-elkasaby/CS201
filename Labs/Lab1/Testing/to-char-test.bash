#!/bin/bash

PROG=to-char
POINTS=0
CLEANUP=1
WARNINGS=0
#DIFF_OPTIONS="-B -w -i"
DIFF_OPTIONS=""

SDIR=.
JDIR=~rchaney/Classes/cs201/Labs/Lab1

while getopts "xC" opt
do
    case $opt in
            x)
                # If you really, really, REALLY want to watch what is going on.
                echo "Hang on for a wild ride."
                set -x
                ;;
            C)
                # Skip removal of data files
                CLEANUP=0
                ;;
            \?)
                echo "Invalid option" >&2
                echo ""
                exit 1
                ;;
            :)
                echo "Option -$OPTARG requires an argument." >&2
                exit 1
                ;;
    esac
done

gcc -Wall -g -o ${PROG} ${PROG}.c 1> out.log 2> warn.log

if [ $? -ne 0 ]
then
    echo "compilation failed"
    echo "zero points"
    exit 1
else
    NUM_BYTES=`wc -c < warn.log`
    if [ ${NUM_BYTES} -ne 0 ]
    then
        WARNINGS=1
        echo "  --- You have compiler warning messages. That is -20 percent!"
    else
        echo "  +++ You have no compiler warning messages. Good job."
        ((POINTS+=5))
    fi
fi

for I in `shuf -i 1-3 -n 3`
do
    ${SDIR}/${PROG} -f < ${JDIR}/${PROG}-${I}.txt > S-toch${I}.out
    ${JDIR}/${PROG} -f < ${JDIR}/${PROG}-${I}.txt > J-toch${I}.out

    diff ${DIFF_OPTIONS} S-toch${I}.out J-toch${I}.out > /dev/null
    if [ $? -eq 0 ]
    then
        ((POINTS+=10))
        echo "  +++ ${PROG} on test file ${PROG}-${I}.txt is good +++"
    else
        echo "  --- ${PROG} on test file ${PROG}-${I}.txt is sad  ---"
        CLEANUP=0
        echo "    try this: diff ${DIFF_OPTIONS} -y S-toch${I}.out J-toch${I}.out"
    fi
done

echo "You have ${POINTS} points out of 35"
if [ ${WARNINGS} -ne 0 ]
then
    POINTS=$(echo ${POINTS}*.8 | bc)
    echo "But, you have compiler warnings"
    echo "  So, you get this many points ${POINTS}"
fi

if [ ${CLEANUP} -eq 1 ]
then
    rm [JS]-toch[123].out out.log warn.log
    rm ${PROG}
fi
