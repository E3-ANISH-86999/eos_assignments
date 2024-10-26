#!/bin/bash

echo -n "Enter a name: "
read name

if [ -e $name ]
then

	if [ -f $name ]
	then
		echo "It is a file!"
		echo -n "Size: "
		stat -c %s $name

	elif [ -d $name ] 
	then
		echo "It is a directory!"
		ls
	fi
else
	echo "$name is neither a file nor a directory!"
fi


