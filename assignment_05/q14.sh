#!/bin/bash

for file in *
do 
	if [ -f "$file" -a -x "$file" ]
	then
		echo "$file"
	fi

done





