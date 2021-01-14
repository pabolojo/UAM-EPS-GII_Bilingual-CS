# Ejemplo script, para P3 arq 2019-2020

#!/bin/bash

# inicializar variables
Ntimes=10
Ninicio=1000000
Npasos=10
Nfinal=100000000
fDATt=time_data.dat
fPNGt=time.png
fDATacc=acc_data.dat
fPNGacc=acc.png

# borrar el fichero DAT y el fichero PNG
rm -f $fDATt $fDATacc

# generar el fichero DAT vacío and raw_data
touch $fDATt $fDATacc

# compile in case needed
make

echo "Running times..."
# bucle para N desde P hasta Q
t_line=0
for i in $(seq $Ninicio $((($Nfinal-$Ninicio+1)/($Npasos-1))) $Nfinal); do
	echo "Size $i/$Nfinal..."

	for time in $(seq 1 1 $Ntimes); do
		t_line=$(./pescalar_serie $i | grep 'Tiempo' | awk -v t=$t_line '{print t+$2}')
	done

	t_line=$(awk -v t=$t_line -v r=$Ntimes 'BEGIN{print t/r}')
	for thr in $(seq 1 1 8); do
		t_par[$thr]=0
		for rep in $(seq 1 1 $Ntimes); do
			t_par[$thr]=$(./pescalar_par3 $i $thr | grep 'Tiempo' | awk -v t=${t_par[$thr]} '{print t+$2}')
		done
		t_par[$thr]=$(awk -v t=${t_par[$thr]} -v r=$Ntimes 'BEGIN{print t/r}')
	done

	echo $i"	"$t_line"	"${t_par[1]}"	"${t_par[2]}"	"${t_par[3]}"	"${t_par[4]}"	"${t_par[5]}"	"${t_par[6]}"	"${t_par[7]}"	"${t_par[8]} >> $fDATt
	awk -v size=$i -v t=$t_line -v t1=${t_par[1]} -v t2=${t_par[2]} -v t3=${t_par[3]} -v t4=${t_par[4]} -v t5=${t_par[5]} -v t6=${t_par[6]} -v t7=${t_par[7]} -v t8=${t_par[8]} 'BEGIN{print size"	"t/t1"	"t/t2"	"t/t3"	"t/t4"	"t/t5"	"t/t6"	"t/t7"	"t/t8}' >> $fDATacc
done

# llamar a gnuplot para generar el gráfico y pasarle directamente por la entrada
# estándar el script que está entre "<< END_GNUPLOT" y "END_GNUPLOT"
echo "Generating plot..."
gnuplot << END_GNUPLOT
set title "Execution Time of Vector Product"
set ylabel "Time (s)"
set xlabel "Vector Size"
set key right bottom
set grid
set term png
set output "$fPNGt"
plot "$fDATt" using 1:2 with lines lw 2 title "Serial", \
	 "$fDATt" using 1:3 with lines lw 2 title "1 thread", \
     "$fDATt" using 1:4 with lines lw 2 title "2 threads", \
     "$fDATt" using 1:5 with lines lw 2 title "3 threads", \
     "$fDATt" using 1:6 with lines lw 2 title "4 threads", \
	 "$fDATt" using 1:7 with lines lw 2 title "5 threads", \
	 "$fDATt" using 1:8 with lines lw 2 title "6 threads", \
	 "$fDATt" using 1:9 with lines lw 2 title "7 threads", \
	 "$fDATt" using 1:10 with lines lw 2 title "8 threads"
	 
replot
set title "Vector Product Acceleration"
set ylabel "Acceleration"
set output "$fPNGacc"
plot "$fDATacc" using 1:2 with lines lw 2 title "1 thread", \
     "$fDATacc" using 1:3 with lines lw 2 title "2 threads", \
     "$fDATacc" using 1:4 with lines lw 2 title "3 threads", \
     "$fDATacc" using 1:5 with lines lw 2 title "4 threads", \
	 "$fDATacc" using 1:6 with lines lw 2 title "5 threads", \
	 "$fDATacc" using 1:7 with lines lw 2 title "6 threads", \
	 "$fDATacc" using 1:8 with lines lw 2 title "7 threads", \
	 "$fDATacc" using 1:9 with lines lw 2 title "8 threads"
replot
quit
END_GNUPLOT
