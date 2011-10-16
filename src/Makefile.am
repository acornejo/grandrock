bin_PROGRAMS = grandrock

grandrock_SOURCES = grandrock.cc xrandr-query.h

grandrock_LDADD = $(GR_LIBS)

AM_CPPFLAGS = $(GR_CFLAGS) -DPIXMAPS_DIR=\""$(pkgdatadir)"\"

again: clean all
