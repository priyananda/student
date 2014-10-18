include ../../defs.mk

# Files to be created.
OBJS=DefaultPlugin.o

# Dependencies.
all : $(PLUGINS)

$(PLUGINDIR)/default.so:: DefaultPlugin.o
	@echo Creating $@
	@g++ -o $@ $(PFLAGS) DefaultPlugin.o

# Clean up everything.
clean:
	rm -f $(OBJS) $(PLUGINS)
