#!/bin/bash
while true
do	
	echo -e "Enter password: \c"
	read -s pass1
	echo " "
	[ -z "$pass1" ] || break
done
while [ "$pass1" != "$pass2" ] 
do	
	echo -e "Renter password: \c"
	read -s pass2
	echo " "
done
clear
trap '' SIGINT SIGTERM SIGSTOP SIGTSTP SIGHUP SIGKILL
echo "---------------------Terminal locked-------------------------"
while [ "$pass" != "$pass1" ] 
do	
	echo -e "Enter password to unlock: \c"
	read -s pass
	echo " "
done
echo "---------------------Terminal Unlocked-------------------------"
