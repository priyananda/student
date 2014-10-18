#!/bin/bash
function findMax {
	dir=$1
#	ls -lR $dir | tr -s " " | cut -d " " -f5,9 | sort -n -r | head -1
	for x 
	do
		echo $x	
	done
}
if [ $# -eq 0 ] 
then
	echo "Error"
	exit 1024
fi
findMax `ls -l question.txt`
