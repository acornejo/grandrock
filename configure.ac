AC_PREREQ(2.52)

AC_INIT(grandrock, 0.1.0, acornejo@gm*l.com)
AC_CONFIG_SRCDIR(src/grandrock.cc)
AM_CONFIG_HEADER(src/config.h)

AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_INTLTOOL([0.35.0])
AC_STDC_HEADERS

AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)

GLIB_REQUIRED=2.6.0
GTK_REQUIRED=2.12.0

AC_SUBST(GLIB_REQUIRED)
AC_SUBST(GTK_REQUIRED)

PKG_CHECK_MODULES(GR, glib-2.0 >= $GLIB_REQUIRED
                       gobject-2.0 gthread-2.0
                       gtk+-2.0 >= $GTK_REQUIRED
                       gconf-2.0 >= $GCONF_REQUIRED)

AC_SUBST(GR_CFLAGS)
AC_SUBST(GR_LIBS)

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 data/Makefile
                 data/grandrock.desktop])
AC_CONFIG_COMMANDS([default], [[ echo timestamp > stamp-h ]], [[]])
AC_OUTPUT
