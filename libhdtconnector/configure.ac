AC_PREREQ(2.65)
LT_PREREQ([2.4.0])
AC_INIT([hdtconnector], [1.0], [pablo.torres.t@gmail.com])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([build])
AC_CONFIG_HEADERS([src/config.h])
AM_INIT_AUTOMAKE([foreign])
AM_SILENT_RULES([yes]) # Silent bulding

AC_PROG_CXX # Define CXX compiler
gl_EARLY
AC_LANG([C++])
AC_PROG_INSTALL
AC_PROG_CPP
AM_PROG_AR # Define AR (archiver)
LT_INIT([shared static]) # Must be called after CXX AR
AX_CXX_COMPILE_STDCXX_11([noext],[mandatory])

# Find HDT 
PKG_CHECK_MODULES([HDT], [hdt],[
  CPPFLAGS="$HDT_CFLAGS $CPPFLAGS"
  LIBS="$HDT_LIBS $LIBS"
])
AC_CHECK_HEADERS([HDT.hpp], [], 
  AC_MSG_ERROR([Could not find HDT.hpp]))

# Find boost-python
AX_BOOST_PYTHON

# Find a recent glib version. If not, then use boost locale
AC_CHECK_HEADER([codecvt],
  [AC_DEFINE([HAVE_CODECVT], [1], [Have GLIB 2X])]
  [enable_boost_locale=no],
  [AX_BOOST_LOCALE]
  [enable_boost_locale=yes]
  )
AM_CONDITIONAL([WANTS_BOOST_LOCALE],[ test "x$enable_boost_locale != xno"])

# Find numpy headers
numpy_import=$(python -c "import numpy; print(numpy.get_include())")
AS_IF(test ! -z $numpy_import,
	O_CPPFLAGS="$CPPFLAGS"
	CPPFLAGS="-I$numpy_import $PYTHON_CPPFLAGS $CPPFLAGS"
	)
AC_CHECK_HEADER([numpy/arrayobject.h],
	[AC_SUBST(NUMPY_CPPFLAGS, ["-I$numpy_import"])]
	[AC_SUBST(NUMPY_LIBS, ["-lboost_numpy3"])]
	[CPPFLAGS="$O_CPPFLAGS"],
	[AC_MSG_ERROR([Could not find numpy headers])]
	)

gl_INIT
gl_WARN_ADD([-Wno-return-type],[WARN_CFLAGS])
gl_COMPILER_OPTION_IF([-fpermissive], [WARN_CFLAGS="-fpermissive $WARN_CFLAGS"])
AC_CONFIG_FILES([
  Makefile
  src/Makefile
])
AC_OUTPUT
