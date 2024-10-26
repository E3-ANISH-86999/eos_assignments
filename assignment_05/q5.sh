#!/bin/bash

echo "Find max of three"

echo -n -e "Enter n1 : "
read n1

echo -n -e "Enter n2 : "
read n2

echo -n -e "Enter n3 : "
read n3

if [ $n1 -lt $n2 ]
then 
	if [ $n3 -lt $n2 ]
	then
		echo "$n2 is greater than $n1 and $n3"
	fi
else
	if [ $n3 -lt $n1 ]
	then
		echo "$n1 is greater than $n2 and $n3"
	else  
		echo  "$n3 is greater than $n1 and $n2"
	fi
fi










