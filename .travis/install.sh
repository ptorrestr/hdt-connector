#!/usr/bin/env bash

set -x -e

if [[ "$TRAVIS_OS_NAME" == "osx" ]]; then
  rvm get stable # We need this since there is a bug in osx. See https://github.com/travis-ci/travis-ci/issues/6307
  os="MacOSX"
else
  os="Linux"
fi

python_v="3"
wget "https://repo.continuum.io/miniconda/Miniconda${python_v}-latest-${os}-x86_64.sh" -O miniconda.sh;
bash miniconda.sh -b -p $HOME/miniconda
export PATH="$HOME/miniconda/bin:$PATH"
hash -r
conda config --set always_yes yes --set changeps1 no
conda update -q conda
conda info -a

conda config --add channels conda-forge
conda config --add channels ptorrestr
conda config --get channels
conda install conda-build anaconda-client
conda update -n root conda-build

conda build .conda/ --no-test --no-anaconda-upload
