#!/bin/bash

if [ -f $1 ]
then 
	echo "File exists!"
	echo -n "Last modification time: "
	stat -c %y $1
else
	echo "File does not exists!!"
fi




