[![Build Status](https://travis-ci.org/ptorrestr/hdt-connector.svg?branch=master)](https://travis-ci.org/ptorrestr/hdt-connector)

HDT Connector
=============

This is a python module to process HDT files.

## Local testing

```
conda-env create --file .conda/environment.yaml
source activate hdtconnector-test
pytest
```

## Build locally with Conda
```
conda build .conda/
```


Installation
------------

* You must first compile and install HDT and Boost libraries (including boost.python lib).
* Once compiled, please provide the respective paths (HDT, Boost) to setup.py
* Boost library should be compiled with the same python version that will be used.
* It is recomendable to use virtualenv to manage the paths when executing. For example you can set LD\_LIBRARY\_PATH in the activation script (MYENV/bin/activate).
* Once the environment is set, you can install the module as normal: ``python setup.py install``

If you have issues with the autotool version, try the following:
``cd hdt-connector && touch configure.ac aclocal.m4 configure Makefile.am Makefile.in``
Then build again.

Usage
-----

To read a HDT file you must use the object HDTConnector and then create a search. Each searching will create an iterator over the collection. For example:

```
from hdtconnector.libhdtconnector import HDTConnector
m_map = HDTConnector("my/path.hdt")

# All the collection
iter = m_map.search("", "", "")
while iter.has_next():
  print( iter.next() )

# Specific subset
resource = "some interesting resource"
iter = m_map.search(resource, "", "")
while iter.has_next():
  print( iter.next() )

```




