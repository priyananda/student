#!/bin/bash
inode=`ls -i $1 | tr -s " " | cut -d " " -f2 | tr -d " "`
ls -RLi $2 | tr -s " " | cut -d " " -f2-  | grep "$inode" | cut -f2 -d " "

