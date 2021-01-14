# GNUPlot con , como separador 1000??
# Se puede bash en gnuplot para loop por cache size?
# Ejemplo script, para P3 arq 2019-2020

#!/bin/bash

# inicializar variables
P=6
Ninicio=$((256 + 256*P))
Npaso=32
Nfinal=$((Ninicio + 256))
fDAT=cache_multiplication.dat

#In order to correctly interpret the floating point numbers
LC_NUMERIC="C"
# compile in case needed
make

rm -f $fDAT 
# generar el fichero DAT vacío and raw_data
touch $fDAT

echo "Running multiplication and multiplication_transpose..."
for ((N = Ninicio ; N <= Nfinal ; N += Npaso)); do
	echo "N: $N / $Nfinal..."
	
	# ejecutar los programas slow y fast consecutivamente con tamaño de matriz N
	# para cada uno, filtrar la línea que contiene el tiempo y seleccionar la
	# tercera columna (el valor del tiempo). Dejar los valores en variables
	# para poder imprimirlos en la misma línea del fichero de datos
	valgrind --tool=cachegrind --cachegrind-out-file=multiplication_raw_cache.dat ./multiplication $N
	valgrind --tool=cachegrind --cachegrind-out-file=multiplication_transpose_raw_cache.dat ./multiplication_transpose $N

	slowTime=$(cg_annotate multiplication_raw_cache.dat | head -n 18 | grep 'PROGRAM TOTALS' | awk '{print $5"\t"$8}')
	fastTime=$(cg_annotate multiplication_transpose_raw_cache.dat | head -n 18 | grep 'PROGRAM TOTALS' | awk '{print $5"\t"$8}')

	echo "$N	$slowTime	$fastTime" >> $fDAT
done

sed -i 's/,//g' $fDAT