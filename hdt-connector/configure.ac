AC_INIT([hdtconnector], [1.0], [pablo.torres.t@gmail.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_CC
AC_PROG_CXX
AM_PROG_AR
LT_INIT # libraries

# LIBS path
AC_CONFIG_MACRO_DIR([m4])
AC_HEADER_STDC

AX_BOOST_BASE([1.57],,) #[AC_MSG_ERROR([Boost was not found in your system])])
AX_BOOST_SYSTEM
AX_BOOST_FILESYSTEM
PKG_CHECK_MODULES([HDT], [hdt-1.0])
#PKG_CHECK_MODULES([boost], [boost-1.57])
PKG_CHECK_MODULES([python], [python])
AC_SUBST([HDT_CFLAGS])
AC_SUBST([HDT_LIBS])

# Check for header files
AC_HEADER_STDC
#AC_CHECK_HEADER_STDBOOL

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
  Makefile
  src/Makefile
])
AC_OUTPUT
