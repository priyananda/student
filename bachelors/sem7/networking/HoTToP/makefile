include defs.mk

# Dependencies.
all: app $(PLUGINS) server

app:
	@make -s -C $(SRCDIR)

plugins:
	@echo creating plugins
	@make -s -C $(SRCDIR)/plugins

$(PLUGINS): $(HOTTOPSO)
	@make -s -C $(SRCDIR)/plugins

# Not so nice but works.
$(HOTTOPSO): $(LIBS)
	@(\
		echo Creating HoTToP.so;\
		mkdir -p $(LIBDIR)/temp;\
		cp $(LIBS) $(LIBDIR)/temp;\
		cd $(LIBDIR)/temp;\
		ar x all.a;\
		g++ -shared *.o -o $@;\
		rm -f all.a *.o\
	)


server: $(HOTTOPSO) $(LIBDIR)/main.o
	@echo Linking server
	@$(CC) $(LFLAGS) -o $@ $(HOTTOPSO) $(LIBDIR)/main.o


$(LIBDIR)/main.o: src/main.cpp
	@(\
		echo -n [Compiling] $<;\
		if $(CC) $(CFLAGS) $(IFLAGS) $< -o $@;\
		then\
			echo -e "\t\t[  OK  ]";\
			exit 0;\
		else\
			echo -e "\t\t[FAILED]";\
			exit 1;\
		fi\
	)


# Clean up everything.
clean:
	@make -s -C $(SRCDIR) clean
	@make -s -C $(SRCDIR)/plugins clean
	@rm -f server $(LIBS) $(HOTTOPSO) $(LIBDIR)/main.o
	@rm -rf $(LIBDIR)/temp
