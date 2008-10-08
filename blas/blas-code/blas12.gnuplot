#plot results for blas1 and blas2 run and compare it to a Pentium Pro (1995)
# Brock Palen 
# brockp@umich.edu
#
#pgcc -fastsse -DACML -DBLAS1 -DBLAS2 blasSpeed.c -lacml -pgf90libs -lpgftnrtl
#
set key below
set xlabel 'N'
set ylabel 'MFlop/s'

plot  'blas12' using 1:2 with lines title 'ACML ddot()',    \
      'blas12' using 1:3 with lines title 'C ddot()',      \
      'blas12' using 1:4 with lines title 'ACML dgemv()',  \
      'blas12' using 1:5 with lines title 'C dgemv()',     \
      200  lt -1 title 'Pentium Pro (1995)'

#pause or plot gone
pause(-1)

#set output 'blas12.png'
#set terminal png size 1024,768
#replot
