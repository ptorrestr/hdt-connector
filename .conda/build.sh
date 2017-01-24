#!/bin/bash

set -x -e

INCLUDE_PATH="-I${PREFIX}/include"
LIBRARY_PATH="-L${PREFIX}/lib"

if [ "$(uname)" == "Darwin" ]; then
  ln -s ${PREFIX}/lib ${PREFIX}/lib64
	MACOSX_VERSION_MIN=10.9
  CXXFLAGS="-mmacosx-version-min=${MACOSX_VERSION_MIN}"
  CXXFLAGS="${CXXFLAGS} -stdlib=libc++ -std=c++11"
  LINKFLAGS="-mmacosx-version-min=${MACOSX_VERSION_MIN}"
  LINKFLAGS="${LINKFLAGS} -stdlib=libc++ -L${LIBRARY_PATH}"

  HDT_CFLAGS=${PREFIX}/include \
    HDT_LIBS=${PREFIX}/lib \
    BOOST_ROOT=${PREFIX} \
    PKG_CONFIG_PATH="${PKG_CONFIG_PATH}" \
    python setup.py install
	unlink ${PREFIX}/lib64
fi

if [ "$(uname)" == "Linux" ]; then
  ln -s ${PREFIX}/lib ${PREFIX}/lib64
  HDT_CFLAGS=${PREFIX}/include \
    HDT_LIBS=${PREFIX}/lib \
    BOOST_ROOT=${PREFIX} \
    PKG_CONFIG_PATH="${PKG_CONFIG_PATH}" \
		CXX=${PREFIX}/bin/g++ \
	  CC=${PREFIX}/bin/gcc \
    python setup.py install
  unlink ${PREFIX}/lib64
fi
