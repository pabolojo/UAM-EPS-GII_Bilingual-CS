#!/bin/bash

declare -A matrix1
declare -A matrix2
declare -A matrix3

read -p "M order of matrices: " m
read -p "N order of matrices: " n

for ((i=0;$i<$m;i=$i+1));do
	for ((j=0;$j<$m;j=$j+1));do
		read -p "Number $(($i+1)),$(($j+1)) of matrix 1: " matrix1[$i,$j]
	done
done

for ((i=0;$i<$m;i=$i+1));do
	for ((j=0;$j<$m;j=$j+1));do
		read -p "Number $(($i+1)),$(($j+1)) of matrix 2: " matrix2[$i,$j]
	done
done

echo "Sum: "

for ((i=0;$i<$m;i=$i+1));do
	for ((j=0;$j<$m;j=$j+1));do
		matrix3[$i,$j]=$((${matrix1[$i,$j]}+${matrix2[$i,$j]}))
		echo -n "${matrix3[$i,$j]} "
	done
	echo " "
done

