bin_PROGRAMS = hdtconnector.so
hdtconnector_so_SOURCES = HDTConnector.cpp ConvertProgress.cpp HDTIterator.cpp hdtconnector_so.cpp
hdtconnector_so_CPPFLAGS = -fPIC -I./include $(HDT_CFLAGS) $(boost_CFLAGS) $(python_CFLAGS)
#libhdtconnector_la_LIBADD = $(HDT_LIBS)/libhdt.a
hdtconnector_so_LDFLAGS = -Wc,-shared -Wl,--export-dynamic $(HDT_LIBS) -lhdt $(boost_LIBS) -lboost_python $(python_LIBS)
