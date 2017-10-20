AC_PREREQ(2.65)
LT_PREREQ([2.4.0])
AC_INIT([hdtconnector], [1.0], [pablo.torres.t@gmail.com])

AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([build])
AC_CONFIG_HEADERS([src/config.h])
m4_include([m4-additional/ax_python_embed.m4])
m4_include([m4-additional/ax_python_devel.m4])
m4_include([m4-additional/ax_boost_base.m4])
m4_include([m4-additional/ax_boost_locale.m4])
m4_include([m4-additional/ax_boost_python.m4])
m4_include([m4-additional/ax_require_defined.m4])
m4_include([m4-additional/ax_cxx_compile_stdcxx.m4])
m4_include([m4-additional/ax_cxx_compile_stdcxx_11.m4])
AM_INIT_AUTOMAKE([1.11 foreign])

AC_PROG_CXX # Define CXX compiler
AC_LANG_CPLUSPLUS # Define CXX for test
AM_PROG_AR # Define AR (archiver)
AM_SILENT_RULES([yes]) # Silent bulding
LT_INIT([shared static]) # Must be called after CXX AR

# Force CXX11
AX_CXX_COMPILE_STDCXX([11],[],[mandatory])

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

AC_CONFIG_FILES([
  Makefile
  src/Makefile
])
AC_OUTPUT
