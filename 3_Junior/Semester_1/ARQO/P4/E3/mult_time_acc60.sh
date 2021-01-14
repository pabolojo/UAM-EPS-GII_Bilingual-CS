#!/bin/bash

Nsize=1750
fDATt=time_data60.dat
fDATa=acc_data60.dat
make

rm -f $fDATt $fDATa

touch $fDATt
touch $fDATa

echo "Executing normal multiplication"
serial=$(./mult $Nsize | grep 'time' | awk '{print $3}')

for i in $(seq 1 1 4); do
    echo "Executing normal multiplication_1 with $i threads"
	mult_1[$i]=$(./mult_1 $Nsize $i | grep 'time' | awk '{print $3}')

	echo "Executing normal multiplication_2 with $i threads"
	mult_2[$i]=$(./mult_2 $Nsize $i | grep 'time' | awk '{print $3}')

	echo "Executing normal multiplication_2 with $i threads"
	mult_3[$i]=$(./mult_3 $Nsize $i | grep 'time' | awk '{print $3}')

	acc_1[$i]=$(echo "scale=6 ; $serial/${mult_1[$i]}" | bc -l)
	acc_2[$i]=$(echo "scale=6 ; $serial/${mult_2[$i]}" | bc -l)
	acc_3[$i]=$(echo "scale=6 ; $serial/${mult_3[$i]}" | bc -l)
done

echo $serial >> $fDATt
echo ${mult_1[1]}"	"${mult_1[2]}"	"${mult_1[3]}"	"${mult_1[4]} >> $fDATt
echo ${mult_2[1]}"	"${mult_2[2]}"	"${mult_2[3]}"	"${mult_2[4]} >> $fDATt
echo ${mult_3[1]}"	"${mult_3[2]}"	"${mult_3[3]}"	"${mult_3[4]} >> $fDATt

echo 1 >> $fDATa
echo ${acc_1[1]}"	"${acc_1[2]}"	"${acc_1[3]}"	"${acc_1[4]} >> $fDATa
echo ${acc_2[1]}"	"${acc_2[2]}"	"${acc_2[3]}"	"${acc_2[4]} >> $fDATa
echo ${acc_3[1]}"	"${acc_3[2]}"	"${acc_3[3]}"	"${acc_3[4]} >> $fDATa