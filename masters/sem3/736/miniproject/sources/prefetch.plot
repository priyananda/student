cd 'results'
set term png

set output 'prefetch_1m.png'
plot 'prefetch_1m.txt'

set output 'prefetch_2m.png'
plot 'prefetch_2m.txt'

set output 'prefetch_4m.png'
plot 'prefetch_4m.txt'

set output 'prefetch_8m.png'
plot 'prefetch_8m.txt'
