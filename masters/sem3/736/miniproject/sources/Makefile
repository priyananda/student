CC = g++ -Wall
SHELL = /bin/bash
PLOT = ls
FILELOC = /ext2

test: clean cleanresults testbuffersize testprefetch testcache testindirection

clean:
	rm -f *.o *.exe

cleanresults:
	rm -f results/*

testbuffersize: buffer_size.exe
	@for (( i = 0 ; i < 100; i = i + 1 )) do ./buffer_size.exe $(FILELOC)/20mb.dat > results/buffer_$$i.txt;  done
	perl collate.pl buffer
	$(PLOT) buffer_size.plot

testprefetch: prefetch.exe
	-./prefetch.exe $(FILELOC)/20mb.dat 1  > results/prefetch_1m.txt
	-./prefetch.exe $(FILELOC)/20mb.dat 2  > results/prefetch_2m.txt
	-./prefetch.exe $(FILELOC)/20mb.dat 4  > results/prefetch_4m.txt
	-./prefetch.exe $(FILELOC)/20mb.dat 8  > results/prefetch_8m.txt
	$(PLOT) prefetch.plot

testcache: cache_size.exe
	-./cache_size.exe $(FILELOC)/1000mb.dat > results/cache_size.txt
	$(PLOT) cache_size.plot

testindirection: indirection.exe
	rm -Rf $(FILELOC)/indirection_*.dat
	@for (( i = 0 ; i < 10; i = i + 1 )) do ./indirection.exe $(FILELOC)/indirection_$$i.dat > results/indirection_$$i.txt;  done
	perl collate.pl indirection
	$(PLOT) indirection.plot

buffer_size.exe: buffer_size.c
	$(CC) -o $@ $<

prefetch.exe: prefetch.c
	$(CC) -o $@ $<

cache_size.exe: cache_size.c
	$(CC) -o $@ $<

indirection.exe: indirection.c
	$(CC) -o $@ $<
