#!/bin/sh
mkdir -p m4
libtoolize --force
aclocal
autoheader
automake --add-missing
autoconf
