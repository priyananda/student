set term  postscript eps enhanced
set key left top
set style data linespoints
set style line 3 lw 3
set pointsize 1
set size 0.6
set ylabel 'Cost(Analytical)'

set output 'case1.eps'
set xlabel 'Number of Attributes in R'
plot 'eval1.txt' using ($1):($2) with linespoint pt 1 lw 3 title 'Row',    \
		''		 using ($1):($3) with linespoints pt 2 lw 3 title 'Column', \
		''		 using ($1):($4) with linespoints pt 4 lw 3 title 'Optimal'

set output 'case2.eps'
set xlabel 'Number of Attributes in R'
plot 'eval2.txt' using ($1):($2) with linespoint pt 1 lw 3  title 'Row',    \
		''		 using ($1):($3) with linespoint pt 2 lw 3  title 'Column', \
		''		 using ($1):($4) with linespoint pt 4 lw 3  title 'Optimal'

set output 'case3.eps'
set xlabel 'Number of Attributes in select clause'
plot 'eval3.txt' using ($1):($2) with linespoint pt 1 lw 3 title 'Row',    \
		''		 using ($1):($3) with linespoint pt 2 lw 3 title 'Column', \
		''		 using ($1):($4) with linespoint pt 4 lw 3  title 'Optimal'

set output 'case4.eps'
set xlabel 'Selectivity'
set xtics 0,0.01,0.05
set key right bottom
plot 'eval4.txt' using ($1):($2) with lines lw 3  title 'Row',    \
		''		 using ($1):($3) with lines lw 3 title 'Column', \
		''		 using ($1):($4) with lines lw 3 title 'Optimal'

set output 'case5.eps'
plot 'eval5.txt' using ($1):($2) with lines lw 3 title 'Row',    \
		''		 using ($1):($3) with lines lw 3 title 'Column', \
		''		 using ($1):($4) with lines lw 3 title 'Optimal'

set output 'case6.eps'
set xlabel 'Write/Read ratio'
set xtics 0,0.5,5
set key left top
plot 'eval6.txt' using ($1):($2) with lines lw 3 title 'Row',    \
		''		 using ($1):($3) with lines lw 3 title 'Column', \
		''		 using ($1):($4) with lines lw 3 title 'Optimal'
