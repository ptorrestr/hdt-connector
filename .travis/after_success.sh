#!/usr/bin/env bash

set -x -e

# If this is a tag
if [ "${TRAVIS_BRANCH}" == "${TRAVIS_TAG}" ]; then
  export PATH="$HOME/miniconda/bin:$PATH"
  file=$(conda build .conda/ --output)
  anaconda -t $ANACONDA_TOKEN upload $file -u $ANACONDA_USER --force
fi
