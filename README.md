HDT Connector
=============

This is a python module to process Dbpedia HDT files.

Installation
------------

* You must first compile and install HDT and Boost libraries.
* Once compiled, please provide the respective paths (HDT, Boost) to setup.py
* It is recomendable to use virtualenv to manage the paths when executing. For example you can set LD\_LIBRARY\_PATH in the activation script (MYENV/bin/activate).
* You can install the module normally: ``python setup.py install``

If you have issues with the autotool version, try the following:
``cd hdt-connector && touch configure.ac aclocal.m4 configure Makefile.am Makefile.in``
Then build again.

Usage
-----

=Read HDT file=
To read a HDT file you must use the object DBpediaHDTConnector. For example:
``
import hdtconnector
my_file = hdtconnector.DBpediaHDTConnector("my/path.hdt")
``



