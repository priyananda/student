#!/bin/bash
day=`date +%e | tr -d " "`
if [ $day -lt 10 ]
then symb="*"
else symb="**"
fi
echo "$symb"
cal | sed "s/\<$day\>/$symb/"

