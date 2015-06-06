####
# This Makefile can be used to make the following:
#	scanner.purecov		This is the "pure coverage" version of the
#				example program that scans Simple tokens
#				from the file named on the command line
#				and writes them to cout.
#
#	scanner.pure		Purified version of the same program.
#
#	scanner (default)	Plain version of the same program (will
#				run faster than the previous two versions).
#
#	test			Run the program's test suite
#
#	view			View pure coverage results.
#
#	clean			Remove generated files.
#
# NOTE: You will probably get a warning message when you create scanner.purecov:
#		Warning: No text segment for coverage tables.
#       You can ignore this warning.
###

###
#set up compiler and options
###
CC = g++
CFLAGS = -g -Wall

# Define which executable to run
P2 = scanner

###
#purify tools on the solaris machines
###
PCOV = /s/std/bin/purecov -log-file=%v.plog
PUR  = /s/std/bin/purify

scanner:main.o scanner.o
	$(CC) $(CFLAGS) -o scanner main.o scanner.o -ll

scanner.purecov: main.o scanner.o
	$(PCOV) $(CC) $(CFLAGS) -o scanner.purecov main.o scanner.o -ll

scanner.pure: main.o scanner.o
	$(PUR) $(CC) $(CFLAGS) -o scanner.pure main.o scanner.o -ll

main.o:	main.cc scanner.h gram.tab.h
	$(CC) $(CFLAGS) -c main.cc

scanner.o: lex.yy.c scanner.h gram.tab.h
	  $(CC) $(CFLAGS) -c lex.yy.c -o scanner.o

lex.yy.c: simple.l
	  flex simple.l

gram.tab.h: scanner.h
	touch gram.tab.h

###
# run tests
###
test:	$(P2)
	@echo "Test 1: no data file -------------------------------------"
	-$(P2)
	@echo "Test 2 ----------------------------------------------"
	-$(P2) test2

###
# view pure coverage results
###
view:	scanner.purecov.pcv
	$(PCOV) -view scanner.purecov.pcv

###
# clean up
###

clean:
	/bin/rm -f core *~ *.o scanner scanner.pure scanner.purecov lex.yy.c *_pure_*.o *.pcv *.plog
