# Ejemplo script, para P3 arq 2019-2020

#!/bin/bash

# inicializar variables
P=6
Ntimes=10
Ninicio=$((10000 + 1024*P))
Npaso=64
Nfinal=$((Ninicio + 1024))
fDAT=time_slow_fast.dat
fPNG=time_slow_fast.png
fRAW=raw_data.dat

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

echo "Running slow and fast..."
# bucle para N desde P hasta Q 
for i in $(seq 1 1 $Ntimes); do
	echo "Iteration $i of $Ntimes..."
	for ((N = Ninicio ; N <= Nfinal ; N += Npaso)); do
		echo "N: $N / $Nfinal..."
		
		# ejecutar los programas slow y fast consecutivamente con tamaño de matriz N
		# para cada uno, filtrar la línea que contiene el tiempo y seleccionar la
		# tercera columna (el valor del tiempo). Dejar los valores en variables
		# para poder imprimirlos en la misma línea del fichero de datos
		slowTime=$(./slow $N | grep 'time' | awk '{print $3}')
		fastTime=$(./fast $N | grep 'time' | awk '{print $3}')

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

echo "Generating plot..."
# llamar a gnuplot para generar el gráfico y pasarle directamente por la entrada
# estándar el script que está entre "<< END_GNUPLOT" y "END_GNUPLOT"
gnuplot << END_GNUPLOT
set title "Slow-Fast Execution Time"
set ylabel "Execution time (s)"
set xlabel "Matrix Size"
set key right bottom
set grid
set term png
set output "$fPNG"
plot "$fDAT" using 1:2 with lines lw 2 title "slow", \
     "$fDAT" using 1:3 with lines lw 2 title "fast"
replot
quit
END_GNUPLOT
