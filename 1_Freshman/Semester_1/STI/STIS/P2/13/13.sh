#!/bin/bash

for ((i=0;$i<6;i=$i+1));do
	read -p "Number $((i+1)): " vector[$((-1*($i-5)))]
done

echo "Vector: ${vector[0]}, ${vector[1]}, ${vector[2]}, ${vector[3]}, ${vector[4]}, ${vector[5]}"
