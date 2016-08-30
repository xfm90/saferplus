#!/bin/bash


SAFERPATH=./

#FILES=10K.jpg
#FILES="10K.jpg 1MB.bmp"
FILES="10K.jpg 1MB.bmp 10MB.bmp"
#FILES=10MB.bmp

TESTS="1 2 3 4"

LOGFILE=results/results-`date "+%Y%m%d-%H%M%S"`.csv

# csv header
echo "Test version; Encrypt/Decrypt; Filename; Try n.; Time (usec)" > $LOGFILE

#main for loop
for N in $TESTS; do

    make clean
    make TEST=-DMEASURE_TEST_$N


printf "\n****\n**** Running Safer++ Measure Test number:  %s\n****\n" $N

#
# Actual encryption/decryption loops
#
for FILE in $FILES; do

    printf "Running Safer++ Encryption ten times on %s...\n" $FILE
    AVG=0

    for f in 1 2 3 4 5 6 7 8 9 10; do
        printf  "\tRun: %s... : " $f
        RESULT=`$SAFERPATH/saferenc $SAFERPATH/files/key.txt $SAFERPATH/files/$FILE $SAFERPATH/files/$FILE.sfr`
	echo $RESULT
	TIME=`echo $RESULT | cut -d\: -f2 | sed "s/\./\,/g"`
	TIME_DOT=`echo $RESULT | cut -d\: -f2`

	AVG=`echo "$AVG + $TIME_DOT / 10" | bc `
	# test version, encr or decr, what file, try num, time taken
	echo "$N, E; $FILE; $f; $TIME" >> $LOGFILE
    done

    printf "%s encryption test done (avg=%s).\n\n" $FILE $AVG

done
#
# Decrypt measure
#
for FILE in $FILES; do

    printf "Running Safer++ Decryption ten times on %s...\n" $FILE
    AVG="0"

    for f in 1 2 3 4 5 6 7 8 9 10; do
        printf  "\tRun: %s... : " $f
        
        RESULT=`$SAFERPATH/saferdec $SAFERPATH/files/key.txt $SAFERPATH/files/$FILE.sfr $SAFERPATH/files/$FILE.out.bmp`
	echo $RESULT
	TIME=`echo $RESULT | cut -d\: -f2 | sed "s/\./\,/g"`
	TIME_DOT=`echo $RESULT | cut -d\: -f2`

	AVG=`echo "$AVG + $TIME_DOT / 10" | bc `

	# test version, encr or decr, what file, try num, time taken
	echo "$N, D; $FILE; $f; $TIME" >> $LOGFILE
    done

    printf "%s descrption test done. (avg=%s)\n\n" $FILE $AVG

done
#
# End  of actual encryption/ decryption loops
#

# close main loop
done 
