
lib_LTLIBRARIES = libhdtconnector.la
libhdtconnector_la_CPPFLAGS = \
	-I./include \
	$(WARN_CFLAGS) \
	$(HDT_CPPFLAGS) \
	$(BOOST_CPPFLAGS) \
	$(PYTHON_CPPFLAGS) \
	$(NUMPY_CPPFLAGS)

libhdtconnector_la_SOURCES = \
	HDTTriple.cpp \
	HDTTripleID.cpp \
	HDTConnector.cpp \
	ConvertProgress.cpp \
	HDTIterator.cpp \
	HDTIteratorTripleID.cpp \
	Utilities.cpp \
	hdtconnector_so.cpp

libhdtconnector_la_LIBADD = 

libhdtconnector_la_LIBTOOLFLAGS = 

libhdtconnector_la_LDFLAGS = \
	$(HDT_LIBS) \
  $(BOOST_LDFLAGS) -l$(BOOST_PYTHON_LIB) \
  $(PYTHON_LIBS) $(PYTHON_EXTRA_LDFLAGS) \
	$(NUMPY_LIBS)

if WANTS_BOOST_LOCALE
libhdtconnector_la_LDFLAGS += $(BOOST_LOCALE_LIB)
endif
