CC    = g++ -Wall -ggdb
OBJS  = Storage.o Meta.o Exec.o MetaPage.o PageManager.o 
OBJS += SlottedPage.o partition.o Marshall.o Handlers.o

all: calfpreprocess calfcreatedb calfoptimize calfexec calfblkload

flash: flmeasure

example:
	#perl script to parse sql
	calfpreprocess student create.sql queries.sql
	#find optimal groups for table
	calfoptimize   student.schema student.query
	#create three databases, one for each layout
	#they will be called XX_row, XX_col, XX_grop
	calfcreatedb   student student.schema
	#run the queries on each db
	calfexec	   student_row student.query
	calfexec	   student_col student.query
	calfexec	   student_grp student.query

calfexec: calfexec.o $(OBJS)
	$(CC) -o $@ $< $(OBJS)

calfoptimize: calfoptimize.o $(OBJS)
	$(CC) -o $@ $< $(OBJS)

calfblkload: calfblkload.o $(OBJS)
	$(CC) -o $@ calfblkload.o $(OBJS)

flmeasure: flashmeasure.o
	$(CC) -o $@ $<

.cc.o:
	$(CC) -c -o $@ $<

clean:
	rm -Rf $(OBJS) calfexec.o calfexec calfoptimize calfoptimize.o test calfblkload calfblkload.o