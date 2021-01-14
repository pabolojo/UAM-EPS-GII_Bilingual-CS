#!/bin/bash

P=1
Nini=$((512 + P)) #512+P
Nend=$((1024 + Nini))
Nstep=64
Ntimes=5
fDATt=time_data.dat
fDATacc=acc_data.dat
fPNGt=time.png
fPNGacc=acc.png
make

rm $fDATt $fDATacc

touch $fDATt
touch $fDATacc

for i in $(seq $Nini $Nstep $Nend); do
	echo "Executing $i/$Nend...."
	SERIE=0
	PAR=0
	for rep in $(seq 1 1 $Ntimes); do
		serial=$(./mult $i | grep 'time' | awk -v t=$serial '{print t+$3}')
		parallel=$(./mult_3 $i 4 | grep 'time' | awk -v t=$parallel '{print t+$3}')
	done

	serial=$(echo "scale=6 ; $serial/$Ntimes" | bc -l)
	parallel=$(echo "scale=6 ; $parallel/$Ntimes" | bc -l)
	acc=$(echo "scale=6 ; $serial/$parallel" | bc -l)

	echo $i"	"$serial"	"$parallel >> $fDATt
	echo $i"	"$acc >> $fDATacc
done

echo "Generating plots..."
gnuplot << END_GNUPLOT
set title "Matrix Product Serial vs Parallel"
set ylabel "Execution Time (s)"
set xlabel "Matrix Size"
set key right bottom
set grid
set term png
set output "$fPNGt"
plot "$fDATt" using 1:2 with lines lw 2 title "Serial", \
     "$fDATt" using 1:3 with lines lw 2 title "Parallel"
	 
replot
set title "Acceleration of Parallel relative to Serial"
set ylabel "Acceleration"
set output "$fPNGacc"
plot "$fDATacc" using 1:2 with lines lw 2
replot
quit
END_GNUPLOT
