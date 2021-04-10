#!/bin/sh
size=`ls -l $2 | awk '{print $5}'`
if [ $size -gt $1 ]
	then
	echo "$2 size is($size) over $1 , error!"
	while [ $# -gt 0 ]
	do
		if [ -f $1 ]
		then
			rm $1
			echo "$1"
		fi
		shift
	done
	exit 1
else
	echo "$2 size is $size"
	exit 0
fi
