include ../../defs.mk

# Files to be created.
OBJS=InetAddress.o Socket.o ServerSocket.o SocketInputStream.o SocketOutputStream.o StringReader.o StringWriter.o

# Dependencies.
all : $(OBJS) $(LIBDIR)/all.a

$(LIBDIR)/all.a: $(OBJS)
	@echo "updating archive all.a"
	@ar ruc $(LIBDIR)/all.a $(OBJS)

# Clean up everything.
clean:
	rm -f $(OBJS)
