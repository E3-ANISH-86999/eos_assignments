#!/bin/bash

#Write a program to calculate gross salary if the DA is 40%, HRA is 20% of basic salary.
#Accept basic salary form user and display gross salary (Result can be floating point value).

echo -e -n "Enter basic salary : "
read sal

DA=`echo "scale=2; $sal * 40 / 100" | bc`
HRA=`echo "scale=2; $sal * 20 / 100" | bc`

gs=`echo "$sal + $DA + $HRA" | bc`

echo "gross salary = $gs"
