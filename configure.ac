AC_PREREQ(2.52)

AC_INIT(grandrock, 0.1.0, acornejo@gmail.com)
AC_CONFIG_SRCDIR(src/grandrock.cc)
AC_CONFIG_HEADERS(src/config.h)

AC_PROG_CXX
AC_PROG_INSTALL

AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)

PKG_CHECK_MODULES(GTK, gtk+-3.0 >= 3.0,,[PKG_CHECK_MODULES(GTK, gtk+-2.0 >= 2.24)])

AC_SUBST(GTK_CFLAGS)
AC_SUBST(GTK_LIBS)

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 data/Makefile
                 data/grandrock.desktop])
AC_CONFIG_COMMANDS([default], [[ echo timestamp > stamp-h ]], [[]])
AC_OUTPUT
