AC_PREREQ(2.52)

AC_INIT(grandrock, 0.1.0, acornejo@gmail.com)
AC_CONFIG_SRCDIR(src/grandrock.cc)
AM_CONFIG_HEADER(src/config.h)

AC_PROG_CXX
AC_PROG_INSTALL

AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)

PKG_CHECK_MODULES(GR, gtk+-3.0 >= 3.0)

AC_SUBST(GR_CFLAGS)
AC_SUBST(GR_LIBS)

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 data/Makefile
                 data/grandrock.desktop])
AC_CONFIG_COMMANDS([default], [[ echo timestamp > stamp-h ]], [[]])
AC_OUTPUT
