# HDT Connector for DBpedia

## Development

Generate autos.
```
./autogen.sh
```

Remove Autoconf staff
```
git clean -f -d -x
```

## Compilation and Installation

* For setting the environment, run `./configure`
* Some relevant variables:
  * HDT\_CFLAGS, HDT\_LIBS: Non standard directory for hdt-cpp lib
  * PYTHON\_VERSION: The python version to use
  * --with-boost: Non standard boost directory
  * Example
  ```
./configure HDT_CFLAGS=/MY/PATH HDT_LIBS=/MY/PATH PYTHON_VERSION=3.2 --with-boost=/MY/PATH
```
* Run make
  ``make && make install``

## Execution
Run ``python`` in the same folder where ``libhdconnector.so`` is stored. Please be aware that ``python`` binary requires that the library paths should be added in ``LD_LIBRARY_PATH`` at the moment of execution. 

Example:
```
LD_LIBRARY_PATH=/opt/usr/local/boost-1.56.0/lib:/home/pablo/workspace/c++/hdt-cpp/hdt-lib python
```
