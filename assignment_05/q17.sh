#!/bin/bash


for i in 1 2 3 4 5
do 
	j=1
	while [ $j -le $i ]
	do
		echo -n "* "
		j=`expr $j + 1`	
	done
	echo " "
done


