#!/bin/bash

PROG=../beczatom

for IN_FILE in *_in.txt; do
	REF_FILE=`echo -n $IN_FILE | sed -e 's/\(.*\)_in\.txt$/\1_out\.txt/'`
	$PROG < $IN_FILE > out.txt
	if ! diff $REF_FILE out.txt ; then
		echo "Fail: $IN_FILE";
		exit
	else
		echo "OK: $IN_FILE";
	fi
	rm out.txt;
done
