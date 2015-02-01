# CS 536 : PA2
# author: priyananda( shenoy@cs.wisc.edu )
# date: 3 Oct 2008
# random quote: 

CC = g++ -Wall
OUT = scanner

main: main.o lex.yy.o helper.o errorhandler.o
	$(CC) -o $(OUT) main.o lex.yy.o helper.o errorhandler.o -ll

lex.yy.o: simple.l
	flex simple.l
	$(CC) -o $@ -c lex.yy.c

.cc.o:
	$(CC) -c -o $@ $<

test: main
#testcase 1 : no argument
	-./$(OUT)
#testcase 2 : invalid file
	-./$(OUT) filenoexists.txt 
#testcase 3 : the main test case
	-./$(OUT) maintest.txt
#testcase 4 : identifiers test case
	-./$(OUT) ids.txt
#testcase 5 : end of file string test case
	-./$(OUT) eofstring.txt
#testcase 6 : keywords and operators
	-./$(OUT) keywords.txt
clean:
	rm -f *.o $(OUT) lex.yy.c
