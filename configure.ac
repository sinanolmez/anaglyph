#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.59])
AC_INIT([anaglyph], [1.00], [ander])
AC_CONFIG_SRCDIR([src/main.cpp])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

AC_PROG_LIBTOOL

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_MAKE_SET

AC_LANG([C++])

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lpthread':
#AC_CHECK_LIB([pthread], [main])

# Check if pkg-config exists on system
PKG_PROG_PKG_CONFIG
# If so, ${PKG_CONFIG} shell variable is defined
# *_CFLAGS and *_LIBS will be substituted
#PKG_CHECK_MODULES([LIBLOG4CXX], [liblog4cxx])
#PKG_CHECK_MODULES([LIBXMLPP], [libxml++-2.6])

# check for libfreeimage
AC_CHECK_HEADER([FreeImage.h],
    [AC_CHECK_LIB([freeimage], [FreeImage_OpenMemory],
        [FREEIMAGE_LIBS="-lfreeimage -lstdc++"], [FREEIMAGE_LIBS=], [-lstdc++])],
    [FREEIMAGE_LIBS=])
AS_IF([test -z "$FREEIMAGE_LIBS"],
    [AC_MSG_ERROR(['libfreeimage' not found])])
AC_SUBST([FREEIMAGE_LIBS], [${FREEIMAGE_LIBS}])

# Check for glut...or freeglut
AC_SEARCH_LIBS(glutGetModifiers, [glut freeglut])

AC_SEARCH_LIBS(glLoadIdentity, [GL], , AC_MSG_ERROR([Opengl not found make sure you have Opengl installed]))
AC_SEARCH_LIBS(glewInit, [GLEW], , AC_MSG_ERROR([Glew not found make sure you have GLEW installed]))

# Checks for header files.
AC_CHECK_HEADERS(GL/gl.h GL/glu.h)
AC_CHECK_HEADER(GL/glut.h)

AC_CHECK_HEADERS([string.h])
AC_CHECK_HEADERS([stdio.h])

AC_CONFIG_MACRO_DIR([m4])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL

# Checks for library functions.
AC_CHECK_FUNCS([strerror])

AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT

echo '

>> Configuration complete, feel free to use
     "make" (compiles the source code)
     "make distcheck" (file distribution check)
     "make run" (run application)
     "make valgrind" (run application using valgrind in order to find memleaks etc.)
     "make check" (build & run test programs located in /tests/)
     "make docs" ([re]generates code documentation and saves it to /docs/ )

'

