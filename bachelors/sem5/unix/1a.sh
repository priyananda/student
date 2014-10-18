#!/bin/bash
if [ $# -eq 0 ] 
then
	echo  -e "Usage:\n$0 ARG [ ARG ]..."
	exit 0
fi
for x in "$@"
do
	str=`echo -e "$x\\\n$str"`
done
echo -e "$str"
