set term png
set style data linespoints
set style line 3 lw 3

set output 'buffer_size.png'
set ylabel 'time to read 512 bytes(microseconds)'
set xlabel 'offset from start_offset(bytes)'
plot 'buffer_size/buffer_average.txt' title 'Buffer size for random reads' with lines linecolor 'black'

set output 'cache_size.png'
set ylabel 'time to read 1 MB (microseconds)'
set xlabel 'data read from end of file(MB)'
plot 'cache_size/cache_size.txt' using (1000-$1):($2)  title 'File system cache size' with lines linecolor 'black';

set output 'indirection.png'
set ylabel 'time to read 4k block (microseconds)'
set xlabel 'data read (kilo bytes)'
plot 'indirection/indirection_average.txt' title '# of Indirect blocks' with lines linecolor 'black'

set output 'prefetch.png'
set ylabel 'time to read 10 kb (microseconds)'
set xlabel 'data read (bytes)'
plot 'prefetch/prefetch_1m.txt' title 'Prefetch during Sequential read' with lines linecolor 'black'
