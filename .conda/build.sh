#!/bin/bash

set -x -e

INCLUDE_PATH="-I${PREFIX}/include"
LIBRARY_PATH="-L${PREFIX}/lib"

if [ "$(uname)" == "Darwin" ]; then
  ln -s ${PREFIX}/lib ${PREFIX}/lib64
  MACOSX_VERSION_MIN=10.11
  CXXFLAGS="-mmacosx-version-min=${MACOSX_VERSION_MIN}"
  CXXFLAGS="${CXXFLAGS} -stdlib=libc++"
  LINKFLAGS="-mmacosx-version-min=${MACOSX_VERSION_MIN}"
  LINKFLAGS="${LINKFLAGS} -stdlib=libc++ -L${LIBRARY_PATH}"

  PKG_CONFIG_PATH="${PKG_CONFIG_PATH}" \
    CXX=${CXX:-llvm-g++} \
    CC=${CC:-llvm-gcc} \
    $PYTHON setup.py install
  unlink ${PREFIX}/lib64
fi

if [ "$(uname)" == "Linux" ]; then
  ln -s ${PREFIX}/lib ${PREFIX}/lib64
  PKG_CONFIG_PATH="${PKG_CONFIG_PATH}" \
    CXX=${CXX:-g++} \
    CC=${CC:-gcc} \
    $PYTHON setup.py install
  unlink ${PREFIX}/lib64
fi
