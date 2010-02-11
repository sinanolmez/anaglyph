#!/bin/sh

if [ -f Makefile ]; then
make clean
rm -f Makefile
fi
rm -f configure
rm -f config.h*
rm -f *.in
rm -f src/*.in
rm -rf autom4te.cache
rm -f aclocal.m4
rm -f config.*
rm -f compile
rm -f depcomp
rm -f missing
rm -f install-sh
rm -f libtool
rm -f ltmain.sh
rm -rf src/.deps
rm -rf src/.libs
rm -f src/Makefile
rm -f stamp-h1
rm -f anaglyph-*.tar.gz
