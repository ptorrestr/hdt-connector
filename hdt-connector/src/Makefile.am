AM_CPPFLAGS = \
	-fPIC -I./include
	$(HDT_CFLAGS) \
	$(BOOST_CFLAGS) \
	$(PYTHON_CFLAGS)

AM_LDFLAGS = \
	$(HDT_LIBS)
	$(BOOST_LDFLAGS)
	$(PYTHON_LIBS)

lib_LTLIBRARIES = libHdtconnector.la
libHdtconnector_la_LIBADD = \
	$(BOOST_FILESYSTEM_LIB) \
	$(BOOST_SYSTEM_LIB)
	


#bin_PROGRAMS = hdtconnector.so
#hdtconnector_so_SOURCES = HDTConnector.cpp ConvertProgress.cpp HDTIterator.cpp hdtconnector_so.cpp
#hdtconnector_so_CPPFLAGS = -fPIC -I./include $(HDT_CFLAGS) $(BOOST_CFLAGS) $(python_CFLAGS)
#libhdtconnector_la_LIBADD = $(HDT_LIBS)/libhdt.a
#hdtconnector_so_LDFLAGS = -Wc,-shared -Wl,--export-dynamic $(HDT_LIBS) -lhdt $(BOOST_LDFLAGS) $(python_LIBS)
