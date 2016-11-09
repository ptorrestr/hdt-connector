AC_PREREQ(2.65)
LT_PREREQ([2.4.0])
AC_INIT([hdtconnector], [1.0], [pablo.torres.t@gmail.com])

AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([1.11 foreign])

AC_PROG_CXX # Define CXX compiler
AC_LANG_CPLUSPLUS # Define CXX for test
AM_PROG_AR # Define AR (archiver)
LT_INIT([shared static]) # Must be called after CXX AR

# Find HDT 
PKG_CHECK_MODULES([HDT], [hdt-1.0],[
  CPPFLAGS="-I$HDT_CFLAGS $CPPFLAGS "
  LDFLAGS="-L$HDT_LIBS $LDFLAGS "
])
AC_CHECK_HEADERS([hdt/HDT.hpp], [], [AC_MSG_ERROR([Could not find HDT.hpp])])

# Find Python
AX_PYTHON_DEVEL([ >= '3.2'])

# Find boost 
AX_BOOST_BASE([1.57], [
], [AC_MSG_ERROR([Could not find Boost Library])])
#AX_BOOST_PYTHON

AC_CONFIG_FILES([
  Makefile
  src/Makefile
])
AC_OUTPUT
