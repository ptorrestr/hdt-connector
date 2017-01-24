#!/usr/bin/env bash

set -e -x

export PATH="$HOME/miniconda/bin:$PATH"
source activate test-environment
conda build -t .conda/
