#!/usr/bin/env bash

set -e -x

export PATH="$HOME/miniconda/bin:$PATH"
conda build -t .conda/
