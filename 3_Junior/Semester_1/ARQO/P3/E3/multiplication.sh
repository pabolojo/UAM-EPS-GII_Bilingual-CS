source multiplication_time.sh
source multiplication_cache.sh

fDAT=mult.dat
fPNGT=mult_time.png
fPNGC=mult_cache.png

rm -f $fDAT $fPNGT $fPNGC
# generar el fichero DAT vacío and raw_data
touch $fDAT
touch $fPNGT
touch $fPNGC

echo "Merging time and cache..."
#Reordering columns to match required pattern
awk 'FNR==NR{time1[$1]=$2; time2[$1]=$3;next}{ print $1"\t"time1[$1]"\t"$2"\t"$3"\t"time2[$1]"\t"$4"\t"$5}' time_multiplication.dat cache_multiplication.dat >> $fDAT

echo "Generating plot cache..."
# llamar a gnuplot para generar el gráfico y pasarle directamente por la entrada
# estándar el script que está entre "<< END_GNUPLOT" y "END_GNUPLOT"
gnuplot << END_GNUPLOT
set title "Matrix Product Data Cache Misses"
set ylabel "Misses"
set xlabel "Matrix Size"
set key right bottom
set grid
set term png
set output "$fPNGC"
plot "$fDAT" using 1:3 with lines lw 2 title "read mult", \
     "$fDAT" using 1:4 with lines lw 2 title "write mult", \
     "$fDAT" using 1:6 with lines lw 2 title "read mult_trans", \
     "$fDAT" using 1:7 with lines lw 2 title "write mult_trans"

replot
quit
END_GNUPLOT

echo "Generating plot time..."
# llamar a gnuplot para generar el gráfico y pasarle directamente por la entrada
# estándar el script que está entre "<< END_GNUPLOT" y "END_GNUPLOT"
gnuplot << END_GNUPLOT
set title "Matrix Product Execution Time"
set ylabel "Execution time (s)"
set xlabel "Matrix Size"
set key right bottom
set grid
set term png
set output "$fPNGT"
plot "$fDAT" using 1:2 with lines lw 2 title "time mult", \
     "$fDAT" using 1:5 with lines lw 2 title "time mult_trans"

replot
quit
END_GNUPLOT
