#!/bin/bash
[ -f Makefile ] && make clean

rm -fR configure config.status depcomp install-sh missing aclocal.m4 autom4te.cache/ config.log src/config.{h,h.in} debian/grandrock* debian/autoreconf* debian/files

find . \( -name Makefile -o -name Makefile.in -o -name "stamp-h*" \) -exec rm -f {} \;
