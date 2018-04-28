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
from itertools import islice
from hdtconnector.libhdtconnector import HDTConnector
m_map = HDTConnector("my/path.hdt")

# Read the 10-first elements in the collection
iter = m_map.search("", "", "")
for triple in islice(iter, 10):
  print( triple.get_subject() )

# Specific subset
resource = "some/interesting/resource"
iter = m_map.search(resource, "", "")
for s,p,o in iter:
  print( "urls s=%s,p=%s,o=%s", %(s,p,o) )

# Search by Ids
from hdtconnector.libhdtconnector import triple_role

id = m_map.uri_to_id( resource, triple_role.subject)
iter = m_map.search_id( id, 0, 0) # 0 means *
for s,p,o in iter:
  print( "ids s=%i,p=%i,o=%i" %(s,p,o) )

# Search by Ids + extended options
iter = m_map.search_id( id, 0, 0, ext = True)
for s,p,o,iss, iso, ilo in iter:
	print( "Is shared subject (%s), is shared object(%s), is literal object(%s)" %(iss, iso, ilo))

```
