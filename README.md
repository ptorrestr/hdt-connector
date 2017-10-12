[![Build Status](https://travis-ci.org/ptorrestr/hdt-connector.svg?branch=master)](https://travis-ci.org/ptorrestr/hdt-connector)

HDT Python Connector
=============

This is a python module for reading HDT files.

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

For reading a HDT file you must use `HDTConnector` object from which you can do a search. Each search will return an iterator with the matching triples. For example:

```python
from hdtconnector.libhdtconnector import HDTConnector
m_map = HDTConnector("my/path.hdt")

# All the collection
iter = m_map.search("", "", "")
while iter.has_next():
  print( iter.next().get_subject() )

# Specific subset
resource = "some interesting resource"
iter = m_map.search(resource, "", "")
while iter.has_next():
  elem = iter.next()
  print( elem.get_subject() )
  print( elem.get_object() )
  print( elem.get_predicate() )

```




