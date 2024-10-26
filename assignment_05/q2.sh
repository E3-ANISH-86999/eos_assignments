#!/bin/bash

while [ 1 ]
do
echo -e "\t1.Date\n\t2.Calender\n\t3.ls\n\t4.pwd\n\t5.Exit\n"
echo -n "Enter your choice : "
read choice

case $choice in
	1) echo -n "Date: " 
		date
		;;
	2) echo "Year 2024 calender"
		cal 2024
		;;
	3) ls
		;;
	4) pwd
		;;
	5) 
		;;
	*) echo "Invalid choice"
esac
echo "Press ctrl + c to exit"

done



