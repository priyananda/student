# CS 536 : HW1
# author: priyananda( shenoy@cs.wisc.edu )
# date: 10 Sep 2008
# random quote: [The Maltese Falcon] Kasper Gutman: The best goodbyes are short. Adieu. 

CC = g++ -Wall

main: main.o symbol.o symboltable.o
	$(CC) -o p1 main.o symbol.o symboltable.o

test: main
#no arguments
	-./p1
#non existent file
	-./p1 thisfiledoesntexist.txt
#duplicate entries
	-./p1 duplicates.txt
#case sensitivity
	-./p1 case.txt
#large file with lots of collisions
	-./p1 hash_collisions.txt

clean:
	rm -f *.o p1

.cc.o:
	$(CC) -c -o $@ $<
