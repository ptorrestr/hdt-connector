AM_CPPFLAGS = \
	-I./include \
	$(HDT_CPPFLAGS) \
	$(BOOST_CPPFLAGS) \
	$(PYTHON_CPPFLAGS)

AM_LDFLAGS = \
	-L$(HDT_LIBS) -lhdt \
	$(BOOST_LDFLAGS) -lboost_python3 \
	$(PYTHON_LDFLAGS) \
	$(PYTHON_EXTRA_LIBS) \
	$(PYTHON_EXTRA_LDFLAGS)

lib_LTLIBRARIES = libhdtconnector.la
libhdtconnector_la_SOURCES = \
	HDTConnector.cpp \
	ConvertProgress.cpp \
	HDTIterator.cpp \
	hdtconnector_so.cpp
libhdtconnector_la_LIBADD = \
	-lz \
        $(AM_LDFLAGS)	


#bin_PROGRAMS = hdtconnector.so
#hdtconnector_so_SOURCES = HDTConnector.cpp ConvertProgress.cpp HDTIterator.cpp hdtconnector_so.cpp
#hdtconnector_so_CPPFLAGS = -fPIC -I./include $(HDT_CFLAGS) $(BOOST_CFLAGS) $(python_CFLAGS)
#libhdtconnector_la_LIBADD = $(HDT_LIBS)/libhdt.a
#hdtconnector_so_LDFLAGS = -Wc,-shared -Wl,--export-dynamic $(HDT_LIBS) -lhdt $(BOOST_LDFLAGS) $(python_LIBS)
