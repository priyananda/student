#!/bin/bash

if [ $# -eq 0 ] 
then
	echo "Usage : $0 [DIRNAME]"
	exit 2
fi
	ls -Rrl $1 | tr -s " " | cut -d " " -f5,9 | sort -nr | head -1
