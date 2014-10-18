#!/bin/bash

if [ $# -eq 0 ]
then
	echo "Seriously man , you have not given any arguments"
	echo "Usage: $0 ARG [ARG]... "
fi

index=$# 
while [ $index -ne 0 ]
do
	eval echo \$$index
	((index=index-1))
done
