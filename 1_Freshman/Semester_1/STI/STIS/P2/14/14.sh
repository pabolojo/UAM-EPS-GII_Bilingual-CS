#!/bin/bash

declare -A array
num=0
for ((i=0;$i<4;i=$i+1));do
	for ((j=0;$j<4;j=$j+1));do
		read -p "Number $(($i+1)),$(($j+1)): " array[$i,$j]
		if [ ${array[$i,$j]} == 0 ];then
			num=$(($num+1));
		fi
	done
done

echo "Matrix:"

for ((i=0;$i<4;i=$i+1));do
	for ((j=0;$j<4;j=$j+1));do
		echo -n "${array[$i,$j]} "
	done
	echo " "
done

echo "Number of Zeros: $num"
