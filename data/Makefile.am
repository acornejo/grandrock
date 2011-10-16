desktopdir = $(datadir)/applications
desktop_in_files = grandrock.desktop.in
desktop_DATA = $(desktop_in_files:.desktop.in=.desktop)

svgicondir = $(datadir)/icons/hicolor/scalable/apps
svgicon_DATA = grandrock.svg

install-data-hook: update-icon-cache
uninstall-hook: update-icon-cache
update-icon-cache:
	gtk-update-icon-cache -f -t $(datadir)/icons/hicolor

EXTRA_DIST = \
        $(icon_DATA) \
        $(svgicon_DATA) \
		$(desktop_DATA)

CLEANFILES = $(desktop_DATA)

DISTCLEANFILES = $(desktop_DATA)
