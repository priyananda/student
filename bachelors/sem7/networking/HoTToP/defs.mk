# Change the directories below to the correct location.
# Directories

XERCESC=/home/harish/xerces
HTTPROOT=/home/harish/sem7/http
LIBDIR=$(HTTPROOT)/lib
SRCDIR=$(HTTPROOT)/src
PLUGINDIR=$(HTTPROOT)/plugins

# Compiler
CC=g++

# Flags
CFLAGS=-c -g
IFLAGS=-I$(XERCESC)/include/ -I$(HTTPROOT)/include/
LFLAGS=-L$(XERCESC)/lib/ -L$(HTTPROOT)/lib/ -lxerces-c -lHoTToP -ldl
PFLAGS=-L$(HTTPROOT)/lib/ -lHoTToP -shared

# Files to be created
HOTTOPSO=$(HTTPROOT)/lib/libHoTToP.so
PLUGINS=$(PLUGINDIR)/default.so
LIBS=$(LIBDIR)/all.a

# Implicit Rules.
.cpp.o:
	@( echo -n [Compiling] $<;\
		if $(CC) $(CFLAGS) $(IFLAGS) $<;\
		then\
			echo -e "\t\t[  OK  ]";\
			exit 0;\
		else\
			echo -e "\t\t[FAILED]";\
			exit 1;\
		fi\
	)
