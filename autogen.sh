#!/bin/sh
# Run this to generate all the initial makefiles, etc.

DIE=0

PACKAGE=grandrock

echo "Generating configuration files for $PACKAGE, please wait..."

(autoconf --version) < /dev/null > /dev/null 2>&1 || {
    echo
    echo "You must have autoconf installed to compile $PACKAGE."
    echo "Download the appropriate package for your distribution,"
    echo "or get the source tarball at:"
    echo
    echo "    ftp://ftp.gnu.org/pub/gnu/autoconf/"
    DIE=1
}

(automake --version) < /dev/null > /dev/null 2>&1 || {
    echo
    echo "You must have automake installed to compile $PACKAGE."
    echo "Download the appropriate package for your distribution,"
    echo "or get the source tarball at:"
    echo
    echo "    ftp://ftp.gnu.org/pub/gnu/automake/"
    DIE=1
}


[ $DIE -eq 1 ] && exit 1;

echo "  aclocal $ACLOCAL_FLAGS"
aclocal $ACLOCAL_FLAGS
echo "  autoheader"
autoheader
echo "  automake --add-missing --copy"
automake --add-missing --copy
echo "  autoconf"
autoconf

if [ -x config.status -a -z "$*" ]; then
	./config.status --recheck
else
    if test -z "$*"; then
        echo "I am going to run ./configure with no arguments - if you wish"
        echo "to pass any to it, please specify them on the $0  command line."
        echo "If you do not wish to run ./configure, press  Ctrl-C now."
        trap 'echo "configure aborted" ; exit 0' 1 2 15
        sleep 1
    fi
    echo "  ./configure ${@}"
    ./configure "$@";
fi
