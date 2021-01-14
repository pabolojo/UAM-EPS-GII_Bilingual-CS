# Ejemplo script, para P3 arq 2019-2020

#!/bin/bash

# inicializar variables
P=6
Ninicio=$((2000 + 512*P))
Npaso=64
Nfinal=$((Ninicio + 512))
fPNGR=cache_lectura.png
fPNGW=cache_escritura.png

cacheL1S=(1024 2048 4096 8192)

#In order to correctly interpret the floating point numbers
LC_NUMERIC="C"
# borrar el fichero DAT y el fichero PNG
rm -f $fPNGR
rm -f $fPNGW
# compile in case needed
make

echo "Running slow and fast..."
# loop for each cache size
for i in "${cacheL1S[@]}"; do
	fDAT=cache_$i.dat
	rm -f $fDAT 
	# generar el fichero DAT vacío and raw_data
	touch $fDAT
	echo "Cache size $i..."
	for ((N = Ninicio ; N <= Nfinal ; N += Npaso)); do
		echo "N: $N / $Nfinal..."
		
		# ejecutar los programas slow y fast consecutivamente con tamaño de matriz N
		# para cada uno, filtrar la línea que contiene el tiempo y seleccionar la
		# tercera columna (el valor del tiempo). Dejar los valores en variables
		# para poder imprimirlos en la misma línea del fichero de datos
		valgrind --tool=cachegrind --cachegrind-out-file=slow_$i.dat --I1=$i,1,64 --D1=$i,1,64 --LL=8388608,1,64 ./slow $N
		valgrind --tool=cachegrind --cachegrind-out-file=fast_$i.dat --I1=$i,1,64 --D1=$i,1,64 --LL=8388608,1,64 ./fast $N

		slowTime=$(cg_annotate slow_$i.dat | head -n 18 | grep 'PROGRAM TOTALS' | awk '{print $5"\t"$8}')
		fastTime=$(cg_annotate fast_$i.dat | head -n 18 | grep 'PROGRAM TOTALS' | awk '{print $5"\t"$8}')

		echo "$N	$slowTime	$fastTime" >> $fDAT
	done
	sed -i 's/,//g' $fDAT
done

echo "Generating plot read..."
# llamar a gnuplot para generar el gráfico y pasarle directamente por la entrada
# estándar el script que está entre "<< END_GNUPLOT" y "END_GNUPLOT"
gnuplot << END_GNUPLOT
set title "Data Cache Read Misses"
set ylabel "Misses"
set xlabel "Matrix Size"
set key right bottom
set grid
set term png
set output "$fPNGR"
plot "cache_1024.dat" using 1:2 with lines lw 2 title "slow 1024", \
     "cache_1024.dat" using 1:4 with lines lw 2 title "fast 1024", \
	 "cache_2048.dat" using 1:2 with lines lw 2 title "slow 2048", \
     "cache_2048.dat" using 1:4 with lines lw 2 title "fast 2048", \
	 "cache_4096.dat" using 1:2 with lines lw 2 title "slow 4096", \
     "cache_4096.dat" using 1:4 with lines lw 2 title "fast 4096", \
	 "cache_8192.dat" using 1:2 with lines lw 2 title "slow 8192", \
     "cache_8192.dat" using 1:4 with lines lw 2 title "fast 8192"
replot
quit
END_GNUPLOT

echo "Generating plot write..."
# llamar a gnuplot para generar el gráfico y pasarle directamente por la entrada
# estándar el script que está entre "<< END_GNUPLOT" y "END_GNUPLOT"
gnuplot << END_GNUPLOT
set title "Data Cache Write Misses"
set ylabel "Misses"
set xlabel "Matrix Size"
set key right bottom
set grid
set term png
set output "$fPNGW"
plot "cache_1024.dat" using 1:3 with lines lw 2 title "slow 1024", \
     "cache_1024.dat" using 1:5 with lines lw 2 title "fast 1024", \
	 "cache_2048.dat" using 1:3 with lines lw 2 title "slow 2048", \
     "cache_2048.dat" using 1:5 with lines lw 2 title "fast 2048", \
	 "cache_4096.dat" using 1:3 with lines lw 2 title "slow 4096", \
     "cache_4096.dat" using 1:5 with lines lw 2 title "fast 4096", \
	 "cache_8192.dat" using 1:3 with lines lw 2 title "slow 8192", \
     "cache_8192.dat" using 1:5 with lines lw 2 title "fast 8192"
replot
quit
END_GNUPLOT
