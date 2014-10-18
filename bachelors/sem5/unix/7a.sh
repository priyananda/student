#!/bin/bash
outFile="pshar.sh"
exec 1> $outFile
echo "#/bin/bash"
for file 
do
	echo "#++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
	echo "#				$file"
	echo "#++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
	echo "cat << 'QWERTY' > $file"
	cat $file
	echo "QWERTY"
done	
