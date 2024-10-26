#!/bin/bash

#print fibonacci series upto number

echo "Print Fibonacci series"

echo -e -n "Enter a number : "
read num


function Fibonacci()
{
n1=0
n2=1
i=2
echo -e -n "$n1\t"
echo -e -n "$n2\t"

while [ $i -le $1 ]
do
	n3=`expr $n2 + $n1`
	echo -e -n "$n3\t"
	n1=$n2
	n2=$n3
	i=`expr $i + 1`
done

echo -e "\n"
}

Fibonacci $num

