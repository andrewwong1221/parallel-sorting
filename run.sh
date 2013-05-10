#!/bin/bash

for THREADS in 0 
do
	printf "$(python -c "print 2**$THREADS") threads\n"
	for EXP in {20..24}
	do
		NUMTHREADS=$(python -c "print 2**$THREADS")
		SIZE=$(python -c "print 2**$EXP")
		printf "$(bin/sort -n $NUMTHREADS -s $SIZE)\n" || exit
	done 
done
