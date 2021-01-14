#!/bin/bash

for ((i=1;$i<11;i=$i+1));do
	read -p "Number $i: " num
	total=$(($total+$num))
done

echo "Total: $total"
