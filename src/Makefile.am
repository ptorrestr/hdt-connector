lib_LTLIBRARIES = libtest.la
libtest_la_SOURCES = main.c DBpediaHDTConnector.cpp ConvertProgress.cpp
libtest_la_CPPFLAGS = -I./include -I$(HDT_CFLAGS) -I$(boost_CFLAGS)
libtest_la_LIBADD = $(HDT_LIBS)/libhdt.a
# We don't include shared, since hdt is static only
libtest_la_LDFLAGS = -static -version-info 0:0:1
