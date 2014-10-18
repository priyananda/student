#!/bin/bash
IFS=/
for dir in $*
do
	mkdir $dir
	cd $dir
	echo "Created dir :`pwd`"
done
