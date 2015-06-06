###
# make a parser for the Simple language
#
# NOTE: "make parse" will not currently work; you need to provide
#       simple.l
###

# set up compiler and options
CC = g++
CFLAGS = -g -Wall

# Define which executable to run
PARSE = parse

#purify tools
PCOV = /s/std/bin/purecov -log-file=%v.plog
PUR  = /s/std/bin/purify

parse: main.o parser.o scanner.o ast.o unparse.o message.o
	$(CC) $(CFLAGS) -o parse main.o parser.o scanner.o ast.o unparse.o message.o -ll

parse.purecov: main.o parser.o scanner.o ast.o unparse.o message.o
	$(PCOV) $(CC) $(CFLAGS) -o parse.purecov main.o parser.o scanner.o ast.o unparse.o message.o -ll

parse.pure: main.o parser.o scanner.o ast.o unparse.o message.o
	$(PUR) $(CC) $(CFLAGS) -o parse.pure main.o parser.o scanner.o ast.o unparse.o message.o -ll

main.o:	main.cc scanner.h parser.h gram.tab.h ast.h
	$(CC) $(CFLAGS) -c main.cc

parser.o: parser.cc parser.h ast.h gram.tab.h gram.tab.c
	$(CC) $(CFLAGS) -c parser.cc

scanner.o: lex.yy.c scanner.h ast.h gram.tab.h
	 $(CC) $(CFLAGS) -c lex.yy.c -o scanner.o

message.o: message.h
	  $(CC) $(CFLAGS) -c message.cc

lex.yy.c: simple.l
	  flex simple.l

ast.o:	ast.cc ast.h list_T.h
	$(CC) $(CFLAGS) -c ast.cc

unparse.o:unparse.cc list_T.h ast.h
	$(CC) $(CFLAGS) -c unparse.cc

parser.h: scanner.h ast.h
	touch parser.h

ast.h:	scanner.h list_T.h
	touch ast.h

###
# the -b flag causes bison to use the given name as a prefix on its output files
# the -d flag causes bison to output gram.tab.h
###
gram.tab.c:	simple.y scanner.h
		bison -b gram -d simple.y

gram.tab.h:	simple.y scanner.h
		bison -b gram -d simple.y


###
# run tests
###
test:	$(PARSE)
	@echo "Test 1: no data file -------------------------------------"
	-$(PARSE)

###
# view pure coverage results
###
view:	parse.purecov.pcv
	$(PCOV) -view parse.purecov.pcv

###
# clean up
###

clean:
	/bin/rm -f core *~ *.o parse parse.pure parse.purecov \
	lex.yy.c gram.tab.c gram.tab.h *_pure_*.o *.pcv *.plog *.out
