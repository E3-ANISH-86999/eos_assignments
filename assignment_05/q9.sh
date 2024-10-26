#!/bin/bash

echo -n "Enter a number: "
read num

i=1
fact=1
while [ $i -le $num ]
do
	fact=`expr $fact \* $i`  
	i=`expr $i + 1`
done

echo "$num! = $fact"

