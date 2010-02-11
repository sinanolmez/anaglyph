## Process this file with automake to produce Makefile.in

AUTOMAKE_OPTIONS = subdir-objects

AM_LIBS = @LIBS@ @FREEIMAGE_LIBS@
AM_CXXFLAGS = -Wall -DGL_GLEXT_PROTOTYPES
AM_LDFLAGS = $(AM_LIBS) $(AM_CXXFLAGS)

bin_PROGRAMS = anaglyph
anaglyph_SOURCES = main.cpp \
Anaglyph.cpp Anaglyph.h \
TextureLoader.cpp TextureLoader.h \
Helper.cpp Helper.h

anaglyph_LDADD = $(AM_LIBS)
anaglyph_LDFLAGS = $(AM_LDFLAGS)
anaglyph_CFLAGS = $(AM_CFLAGS)
