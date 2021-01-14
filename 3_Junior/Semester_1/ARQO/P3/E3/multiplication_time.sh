# Ejemplo script, para P3 arq 2019-2020

#!/bin/bash

# inicializar variables
P=6
Ntimes=10
Ninicio=$((256 + 256*P))
Npaso=32
Nfinal=$((Ninicio + 256))
fDAT=time_multiplication.dat
fRAW=raw_time_data.dat

#In order to correctly interpret the floating point numbers
LC_NUMERIC="C"
# borrar el fichero DAT y el fichero PNG
rm -f $fDAT fPNG

# generar el fichero DAT vacío and raw_data
touch $fDAT

# RAW file, need to do average
touch $fRAW

# compile in case needed
make

echo "Running multiplication and multiplication_transpose..."
# bucle para N desde P hasta Q 
for i in $(seq 1 1 $Ntimes); do
	echo "Iteration $i of $Ntimes..."
	for ((N = Ninicio ; N <= Nfinal ; N += Npaso)); do
		echo "N: $N / $Nfinal..."
		
		# ejecutar los programas slow y fast consecutivamente con tamaño de matriz N
		# para cada uno, filtrar la línea que contiene el tiempo y seleccionar la
		# tercera columna (el valor del tiempo). Dejar los valores en variables
		# para poder imprimirlos en la misma línea del fichero de datos
		slowTime=$(./multiplication $N | grep 'time' | awk '{print $3}')
		fastTime=$(./multiplication_transpose $N | grep 'time' | awk '{print $3}')

		echo "$N	$slowTime	$fastTime" >> $fRAW
	done
done

echo "Calculating average..."
# we create two arrays (one for slow and the other for fast) in which each index (N) contains the sum of the times for that
# particular N (size of input to the program)
# then for every index in the arrays we calculate the average by dividing its value by N, being N the number of oterations
# of the tests, after that we sort the results by N and dump them to $fDAT
awk -v N=$Ntimes '{average_slow[$1] = average_slow[$1] + $2; average_fast[$1] = average_fast[$1] + $3}
				   END {for (item in average_slow){
							print item"\t"average_slow[item]/N"\t"average_fast[item]/N
							}
						}' $fRAW | sort -n -k 1 > $fDAT

# we remove the RAW file
rm -f $fRAW
