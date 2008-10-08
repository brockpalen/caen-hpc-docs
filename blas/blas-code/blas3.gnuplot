#plot results for a blas3 run and compare it to peek performance 
# Brock Palen 
# brockp@umich.edu
#
#pgcc -fastsse -DACML -DBLAS3 blasSpeed.c -lacml -pgf90libs -lpgftnrtl
#
set key below
set xlabel 'N'
set ylabel 'MFlop/s'
set xrange [0:1000]

plot  'blas3.txt' using 1:2 with lines title 'ACML dgemm()',   \
      'blas3.txt' using 1:3 with lines title 'C dgemm()',      \
      5226 title 'Opteron 2218'

#pause or plot gone
pause(-1)

#set output 'blas3.png'
#set terminal png size 1024,768
#replot
