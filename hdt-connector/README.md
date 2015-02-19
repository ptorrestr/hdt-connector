HDT Connector for DBpedia
=========================

Development
------------

Generate autos.
``autoreconf --install``

Installation
-------------

* Run configure specifying the PATH for HDT and BOOST libs.
  ``./configure HDT_CFLAGS=/MY/PATH HDT_LIBS=/MY/PATH boost_CFLAGS=/MY_PATH boost_LIBS=MY_PATH``
  Example:
  ``./configure HDT_CFLAGS=-I/home/pablo/workspace/c++/hdt-cpp/hdt-lib/include HDT_LIBS=-L/home/pablo/workspace/c++/hdt-cpp/hdt-lib boost_CFLAGS=-I/opt/usr/local/boost-1.56.0/include boost_LIBS=-L/opt/usr/local/boost-1.56.0/lib --prefix=/tmp/a``

* Run make
  ``make``
