#!/bin/bash

if [ $# -eq 0 ]
then
	echo "Seriously man , you have not given any arguments"
	echo "Usage: $0 FILE FILE"
fi

file1=$1
file2=$2

if [[ -f $file1 && -f $file2 ]]
then
	echo -n "Read Permission : "
	if [[ -r $file1 ]]
	then
		if [[ -r $file2 ]];then echo "Same";else echo "Different";fi
	else
		if [[ -r $file2 ]];then echo "Different";else echo "Same";fi
	fi
	echo -n "Write Permission : "
	if [[ -w $file1 ]]
	then
		if [[ -w $file2 ]];then echo "Same";else echo "Different";fi
	else
		if [[ -w $file2 ]];then echo "Different";else echo "Same";fi
	fi
	echo -n "Execute Permisiion : "
	if [[ -x $file1 ]]
	then
		if [[ -x $file2 ]];then echo "Same";else echo "Different";fi
	else
		if [[ -x $file2 ]];then echo "Different";else echo "Same";fi
	fi
else
	echo "The files $file1 and/or $file2 are not present"
fi	
