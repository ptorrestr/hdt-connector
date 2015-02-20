bin_PROGRAMS = hdtconnector.so
hdtconnector_so_SOURCES = DBpediaHDTConnector.cpp ConvertProgress.cpp DBpediaHDTConnector_wrap.cpp HDTIterator.cpp HDTUtilities.cpp
hdtconnector_so_CPPFLAGS = -fPIC -I./include $(HDT_CFLAGS) $(boost_CFLAGS) $(python_CFLAGS)
#libhdtconnector_la_LIBADD = $(HDT_LIBS)/libhdt.a
hdtconnector_so_LDFLAGS = -Wc,-shared -Wl,--export-dynamic $(HDT_LIBS) -lhdt $(boost_LIBS) -lboost_python $(python_LIBS)
