bin_PROGRAMS = grandrock

grandrock_SOURCES = grandrock.cc xrandr-query.h

gnome_gmail_notifier_LDADD = $(GR_LIBS)

AM_CPPFLAGS = $(GR_CFLAGS)
              -DPIXMAPS_DIR=\""$(pkgdatadir)"\" \

again: clean all
