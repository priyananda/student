#!/bin/bash
if [ $# -ne 2 ]
then
	echo "Error"
	exit 1
fi
sFile=$2
set -- `ls -l $1`
perm1=$1
echo $perm1 
set -- `ls -l $sFile`
perm2=$1
echo $perm2 
index=2
for x in "User:" "Group:" "Others:"
do
	echo  $x
	for idx in "\tRead :" "\tWrite :" "\tExecute :" 
	do
		p1=`expr substr $perm1 $index 1` 
		p2=`expr substr $perm2 $index 1` 
		echo -e "$idx\c"
		if [ $p1 = $p2 ]
		then
			echo  "Equal"
		else
			echo  "Different"
		fi
		((index=index+1))
	done
done
