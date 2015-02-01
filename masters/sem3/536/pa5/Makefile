# CS 536 : PA4
# author: priyananda( shenoy@cs.wisc.edu )
# date: 2 Nov 2008
# random quote: 

CC = g++ -Wall
PARSE = simple
OFILES  = parser.o lex.yy.o helper.o errorhandler.o unparse.o ast.o main.o symbol.o
OFILES += symboltable.o scopelist.o name-analyzer.o type-checker.o codegen.o generate.o

$(PARSE): $(OFILES)
	$(CC) -o $(PARSE) $(OFILES) -ll

lex.yy.o: simple.l
	flex simple.l
	$(CC) -o $@ -c lex.yy.c

parser.o: gram.tab.h
	$(CC) -o $@ -c gram.tab.c

gram.tab.h: simple.y
	bison -b gram -d simple.y

.cc.o:
	$(CC) -c -o $@ $<

test: parse
#testcase 0 : no argument
	-./$(PARSE)
#testcase 0 : invalid file
	-./$(PARSE) filenoexists.txt
#testcase 1 : 
	-./$(PARSE) test1.sl
#testcase 2 : 
	-./$(PARSE) test2.sl
#testcase 3 : 
	-./$(PARSE) test3.sl
#testcase 4 : 
	-./$(PARSE) test4.sl
#testcase 4 : 
	-./$(PARSE) test5.sl
clean:
	rm -f *.o $(PARSE) lex.yy.c gram.tab.h gram.tab.c
