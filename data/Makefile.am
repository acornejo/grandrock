desktopdir = $(datadir)/applications
desktop_in_files = grandrock.desktop.in
desktop_DATA = $(desktop_in_files:.desktop.in=.desktop)

svgicondir = $(datadir)/icons/hicolor/scalable/apps
svgicon_DATA = grandrock.svg

install-data-hook: update-icon-cache
uninstall-hook: update-icon-cache

gtk_update_icon_cache = gtk-update-icon-cache -f -t $(datadir)/icons/hicolor

update-icon-cache:
	@-if test -w "$(datadir)/icons/hicolor"; then \
		echo "Updating Gtk icon cache."; \
		$(gtk_update_icon_cache); \
	else \
		echo "*** Icon cache not updated.  After (un)install, run this:"; \
		echo "***   $(gtk_update_icon_cache)"; \
	fi

EXTRA_DIST = $(svgicon_DATA) $(desktop_DATA)

CLEANFILES = $(desktop_DATA)

DISTCLEANFILES = $(desktop_DATA)
