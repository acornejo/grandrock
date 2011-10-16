bin_PROGRAMS = grandrock

grandrock_SOURCES = grandrock.cc xrandr-query.h

grandrock_LDADD = $(GTK_LIBS)

AM_CPPFLAGS = $(GTK_CFLAGS) -DPIXMAPS_DIR=\""$(pkgdatadir)"\"

again: clean all
