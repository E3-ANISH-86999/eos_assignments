#!/bin/bash

echo "Enter a Number: "
read num

flag=0
i=2
while [ $i -le `expr $num / 2` -a $flag -eq 0 ]
do 
	if [ `expr $num % $i` -eq 0 ]
	then
		echo "$num is not a prime number."
		flag=1
	fi
	i=`expr $i + 1`
done


if [ $flag -eq 0 ]
then
	echo "$num is a prime number!"
fi

























