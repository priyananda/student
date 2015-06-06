# CS 536 : PA3
# author: priyananda( shenoy@cs.wisc.edu )
# date: 23 Oct 2008
# random quote: 

CC = g++ -Wall
OUT = parse

parse: parser.o lex.yy.o helper.o errorhandler.o unparse.o ast.o main.o
	$(CC) -o $(OUT) main.o lex.yy.o helper.o errorhandler.o parser.o unparse.o ast.o -ll

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
	-./$(OUT)
#testcase 0 : invalid file
	-./$(OUT) filenoexists.txt
#testcase 1 : example.simple
	-./$(OUT) test1.sl
#testcase 2 : operator precedence
	-./$(OUT) test2.sl
#testcase 3 : empty file
	-./$(OUT) test3.sl
#testcase 4 : main test case
	-./$(OUT) test4.sl
clean:
	rm -f *.o $(OUT) lex.yy.c gram.tab.h gram.tab.c
