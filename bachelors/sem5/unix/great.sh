#!/bin/bash

if [ $# -eq 0 ]
then
	echo "Seriously man , you have not given any arguments"
	echo "Usage: $0 NUMBER NUMBER NUMBER "
fi

great=$1
if [[ $great < $2 ]]
then
	great=$2
fi
if [[ $great < $3 ]]
then
	great=$3
fi	

echo "Greater of $1 $2 $3 is $great"

