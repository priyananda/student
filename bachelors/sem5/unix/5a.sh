#!/bin/bash
for user
do
	dirName=`eval echo ~$user`
	if [ -d $dirName -a ! $dirName = ~$user ]
	then
		echo "Home of $user : $dirName"
	else
		echo "$user is dead"
	fi
done	
