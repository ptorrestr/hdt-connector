AC_INIT([hdtconnector], [1.0], [pablo.torres.t@gmail.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_CC
AC_PROG_CXX
AM_PROG_AR
LT_INIT # libraries

# LIBS path
PKG_CHECK_MODULES([HDT], [hdt-1.0])
PKG_CHECK_MODULES([boost], [boost-1.57])
PKG_CHECK_MODULES([python], [python2])
AC_SUBST([HDT_CFLAGS])
AC_SUBST([HDT_LIBS])

# Check for header files
AC_HEADER_STDC
#AC_CHECK_HEADER_STDBOOL

#have_hdt=no
#AC_SEARCH_LIBS([HDTManager], [hdt], [have_hdt=yes],[have_hdt=no])
#AC_CHECK_HEADERS([HDTManager.hpp],[have_hdt=yes],[have_hdt=no])
#if test "x${have_hdt}" = xno; then
#  echo "------------------------------------------"
#  echo " The HDT library and header file is       "
#  echo " required to build the connector.         "
#  echo " Check 'config.log' for more information. "
#  echo "------------------------------------------"
#  (exit 1); exit 1;
#fi
AC_CONFIG_MACRO_DIR([m4])
#AC_CONFIG_MACRO_DIRS([m4])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
  Makefile
  src/Makefile
])
AC_OUTPUT
