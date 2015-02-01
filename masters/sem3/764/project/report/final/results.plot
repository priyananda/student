set term  postscript eps enhanced
set key left top
set style data linespoints
set style line 3 lw 3
set pointsize 1
set size 0.6
set ylabel 'Time(milliseconds)'

set output 'res1.eps'
set xlabel 'Number of Attributes in R'
plot 'eval1_res.txt' using ($1):($2) with linespoints lt 3  lw 3 title 'Row',    \
	 '' 			 using ($1):($3) with linespoints lt 2  lw 3 title 'Column'

set output 'res2.eps'
set xlabel 'Number of Attributes in R'
plot 'eval2_res.txt' using ($1):($2) with linespoint pt 1  lw 3 title 'Row',    \
		''		 	 using ($1):($3) with linespoint pt 2  lw 3 title 'Column', \
		''		 	 using ($1):($4) with linespoint pt 4  lw 3 title 'Optimal'

set output 'res3.eps'
set xlabel 'Number of Attributes in select clause'
plot 'eval3_res.txt' using ($1):($2) with linespoint pt 1  lw 3 title 'Row',    \
		''		 	 using ($1):($3) with linespoint pt 2  lw 3 title 'Column', \
		''		 	 using ($1):($4) with linespoint pt 4  lw 3 title 'Optimal'

set output 'res4.eps'
set xlabel 'Selectivity'
set xtics 0,0.001,0.005
set key right bottom
plot 'eval4_res.txt' using ($1):($2) with lines lw 3 title 'Row',    \
		''		 	 using ($1):($4) with lines lw 3 title 'Column', \
		''		 	 using ($1):($3) with lines lw 3 title 'Optimal'

set output 'res5.eps'
plot 'eval5_res.txt' using ($1):($2) with lines lw 3 title 'Row',    \
		''		 	 using ($1):($3) with lines lw 3 title 'Column', \
		''		 	 using ($1):($4) with lines lw 3 title 'Optimal'
