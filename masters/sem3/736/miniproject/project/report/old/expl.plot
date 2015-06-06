set term  png
set key left top
set style data lines
set size 0.6,0.7

set title 'Ideal and Actual Window size'
set output 'exp1.png'
set xlabel 'time'
set ylabel 'window size (blocks read)'
plot 'actual_window.txt' using ($1):($2) lc rgbcolor 'black' lw 2 title 'Ideal window size',    \
		''		 using ($1):($3) lc rgbcolor 'red'   lw 2 title 'Actual window size'
		
set title 'Calculating Ideal Window size'
set output 'exp2.png'
set xlabel 'time'
set ylabel 'window size (blocks read)'
plot 'ideal_calc.txt' 	using ($1):($2) lc rgbcolor 'black' lw 2 title 'Read Rate',    \
	 ''		 			using ($1):($3) lc rgbcolor 'red'   lw 2 title 'Cache Pressure', \
	 ''					using ($1):($4) lc rgbcolor 'blue'  lw 2 title 'Ideal window size'