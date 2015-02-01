set term png
set style line 3 lw 3

set output '4d.png'
set xlabel 'Learning rate' font "Arial, 24"
set ylabel 'Accuracy (%)' font "Arial, 24"
set title  'Accuracy varying with learning rate' font "Arial, 24"
plot '4d_data.txt' with lines lw 3