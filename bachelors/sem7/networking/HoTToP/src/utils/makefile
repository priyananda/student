include ../../defs.mk

# Files to be created.
OBJS=DynamicLoader.o ConfigManager.o ConfigExtractor.o StringUtils.o File.o

# Dependencies.
all : $(OBJS) $(LIBDIR)/all.a

$(LIBDIR)/all.a: $(OBJS)
	@echo Updating archive all.a
	@ar ruc $(LIBDIR)/all.a $(OBJS)

# Clean up everything.
clean:
	rm -f $(OBJS)
