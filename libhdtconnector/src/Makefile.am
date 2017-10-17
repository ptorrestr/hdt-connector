
lib_LTLIBRARIES = libhdtconnector.la
libhdtconnector_la_CPPFLAGS = \
	-I./include \
        $(BOOST_CPPFLAGS) \
        $(PYTHON_CPPFLAGS) 

libhdtconnector_la_SOURCES = \
	HDTTriple.cpp \
	HDTTripleID.cpp \
	HDTConnector.cpp \
	ConvertProgress.cpp \
	HDTIterator.cpp \
	HDTIteratorTripleID.cpp \
	hdtconnector_so.cpp

libhdtconnector_la_LIBADD = 

libhdtconnector_la_LIBTOOLFLAGS = 

libhdtconnector_la_LDFLAGS = \
	-lhdt \
        $(BOOST_LDFLAGS) -l$(BOOST_PYTHON_LIB) \
        $(PYTHON_LIBS) \
	$(PYTHON_EXTRA_LDFLAGS) 
