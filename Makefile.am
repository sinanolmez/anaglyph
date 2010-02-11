## Process this file with automake to produce Makefile.in

ACLOCAL_AMFLAGS = -I m4
MAINPROG = anaglyph
CLEANFILES = $(MAINPROG)
SUBDIRS = src

all-am: $(MAINPROG)
	
	
$(MAINPROG):
	echo "LD_LIBRARY_PATH=@LIB_PATH@:/usr/pkg/lib src/$(MAINPROG)" > ./$(MAINPROG)
	chmod u+x $(MAINPROG)

.PHONY: run
run: all
	./$(MAINPROG)

.PHONY: docs
docs: clean-docs
	doxygen cfg/doxygen.cfg
	
clean-local: clean-docs

.PHONY: clean-docs
clean-docs:
	rm -rf docs/html
	

.PHONY: valgrind
valgrind: all
	valgrind --leak-check=full ./$(MAINPROG)

