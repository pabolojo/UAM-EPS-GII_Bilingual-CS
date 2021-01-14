#!/bin/bash

total=0
read -p "Salary per hour: " salph
read -p "Number of workers: " worknum

for ((i=1;$i<$(($worknum +1));i=$i+1));do
	daysaweek=0
	hours=0
	sal=0
	read -p "Worker $i days a week: " daysaweek
	for ((j=1;$j<$(($daysaweek +1));j=$j+1));do
		read -p "Worker $i hours of day $j: " hours
		sal=$(($sal+$hours*$salph))
	done
	echo "Worker $i salary: $sal"
	total=$(($total+$sal))
done

echo "Total: $total"
