include ../../defs.mk

# Files to be created.
OBJS=Handler.o Realm.o Server.o HeaderParser.o RequestDispatcher.o Plugin.o HttpErrorHandler.o


# Dependencies.
all : $(OBJS) $(LIBDIR)/all.a

$(LIBDIR)/all.a: $(OBJS)
	@echo Updating archive all.a
	@ar ruc $(LIBDIR)/all.a $(OBJS)

# Clean up everything.
clean:
	rm -f $(OBJS)
