#!/bin/bash

H2F=hex-2-float
SUCCESS=0
TOTAL_POINTS=0
CLEANUP=1
#DIFF_OPTIONS="-B -w -i"
DIFF_OPTIONS=""
TIMEOUT=5

SDIR=.
JDIR=~rchaney/Classes/cs201/Labs/Lab2

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

function testStdin {
    FILE=$1
    shift
    OPTIONS=$*

    echo -e "\n\nComparison stdin: ${FILE}  with options: ${OPTIONS}"
    
    timeout ${TIMEOUT} ${SDIR}/${H2F} ${OPTIONS} < ${FILE} > SI-${FILE} 2> /dev/null
    if [ $? -eq 124 ]
    then
        echo ">>> command timed out - this is very bad <<<   ./${H2F} ${OPTIONS} < ${FILE}"
        return
    fi
    
    ${JDIR}/${H2F} ${OPTIONS} < ${FILE} > JI-${FILE} 2> /dev/null

    diff ${DIFF_OPTIONS} JI-${FILE} SI-${FILE} > /dev/null

    if [ $? -eq 0 ]
    then
        echo -e "\t*** all is good ***  +12"
        ((TOTAL_POINTS+=12))
    else
        echo -e "\t--- did not compare the same ---"
        CLEANUP=0
        
        DIFF_COUNT=$(diff ${DIFF_OPTIONS} JI-${FILE} SI-${FILE} | wc -l)
        echo -e "\tline diff count: ${DIFF_COUNT}"
        
        echo -e "\ttry this: diff ${DIFF_OPTIONS} -y JI-${FILE} SI-${FILE} | less"
        LC=$(wc -l < SI-${FILE})
        if [ ${LC} -eq 1 ]
        then
            echo -e "\tOnly one line of output. You probably did not read all the input."
        fi
    fi
}

function testFile {
    FILE=$1
    shift
    OPTIONS=$*

    echo -e "\n\nComparison file: ${FILE}  with options: ${OPTIONS}"
    timeout ${TIMEOUT} ${SDIR}/${H2F} ${OPTIONS} -i ${FILE} > SF-${FILE} 2> /dev/null
    if [ $? -eq 124 ]
    then
        echo ">>> command timed out - this is very bad <<<   ./${H2F} ${OPTIONS} -i ${FILE}"
        return
    fi

    ${JDIR}/${H2F} ${OPTIONS} -i ${FILE} > JF-${FILE} 2> /dev/null

    diff ${DIFF_OPTIONS} JF-${FILE} SF-${FILE} > /dev/null

    if [ $? -eq 0 ]
    then
        echo -e "\t*** all is good ***  +12"
        ((TOTAL_POINTS+=12))
    else
        echo -e "\t--- did not compare the same ---"
        CLEANUP=0

        DIFF_COUNT=$(diff ${DIFF_OPTIONS} JF-${FILE} SF-${FILE} | wc -l)
        echo -e "\tline diff count: ${DIFF_COUNT}"

        echo -e "\ttry this: diff ${DIFF_OPTIONS} -y JF-${FILE} SF-${FILE} | less"
        LC=$(wc -l < SF-${FILE})
        if [ ${LC} -eq 1 ]
        then
            echo -e "\tOnly one line of output. You probably did not read all the input."
        fi
    fi
}

rm -f *.o ${H2F}
make -s ${H2F}

if [ ! -e ${H2F} ]
then
    echo "cannot find ${H2F}"
    exit 1
fi

ln -sf ${JDIR}/hex-*.txt .

${SDIR}/${H2F} -v < /dev/null > S-verbose-out.txt 2> S-verbose-err.txt
if [ -s S-verbose-err.txt ]
then
    ((TOTAL_POINTS+=6))
    echo "VERBOSE: +6"
    cat S-verbose-err.txt
else
    #if [ -e S-verbose-out.txt -a -s S-verbose-out.txt ]
    echo "The verbose output is supposed to go to stderr: -5"
fi

${SDIR}/${H2F} -H < /dev/null > S-help-out.txt 2> S-help-err.txt
if [ ! -s S-help-out.txt -o ! -s S-help-err.txt ]
then
    ((TOTAL_POINTS+=6))
    echo "HELP: +6"
    cat S-help-out.txt S-help-err.txt
else
    #if [ -e S-verbose-out.txt -a -s S-verbose-out.txt ]
    echo "Where is the -H output? -5"
fi

testStdin hex-bfloat16-1-8-7.txt -b
testStdin hex-double64-1-11-52.txt -d
testStdin hex-float16-1-5-10.txt -h
testStdin hex-float32-1-8-23.txt
testStdin hex-float5-1-2-2.txt -e 2 -f 2
testStdin hex-float8-1-4-3.txt -e 4 -f 3
testStdin hex-minifloat-1-4-3.txt -m

testFile hex-bfloat16-1-8-7.txt -b
testFile hex-double64-1-11-52.txt -d
testFile hex-float16-1-5-10.txt -h
testFile hex-float32-1-8-23.txt
testFile hex-float5-1-2-2.txt -e 2 -f 2
testFile hex-float8-1-4-3.txt -e 4 -f 3
testFile hex-minifloat-1-4-3.txt -m

echo -e "\n\nTotal points: ${TOTAL_POINTS}"

if [ ${CLEANUP} -eq 1 ]
then
    rm [JS]-*.txt [JS][IF]-*.txt hex-[bdfm]*.txt
    rm ${H2F} ${H2F}.o
fi
