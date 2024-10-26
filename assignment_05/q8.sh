#!/bin/bash

echo -n "Enter a number: "
read num

echo "Table of $num: "

i=1
while [ $i -le 10 ]
do
	echo -e "\t`expr $i \* $num`"
	
	i=`expr $i + 1`
done







