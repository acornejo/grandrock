desktopdir = $(datadir)/applications
desktop_in_files = grandrock.desktop.in
desktop_DATA = $(desktop_in_files:.desktop.in=.desktop)

NULL = 

public_icons = \
	hicolor_apps_scalable_grandrock.svg \
	ubuntu-mono-dark_apps_scalable_grandrock.svg \
	ubuntu-mono-light_apps_scalable_grandrock.svg \
	$(NULL)

gtk_update_icon_cache = gtk-update-icon-cache -f -t

update-icon-cache:
	@-for icon in $(public_icons); do \
		THEME=`echo $$icon | cut -d _ -f1`; \
		if [ -w "$(DESTDIR)$(datadir)/icons/$$THEME" ]; then \
			echo "Updating $$THEME GTK icon cache."; \
			$(gtk_update_icon_cache) $(DESTDIR)$(datadir)/icons/$$THEME; \
		else \
			echo "*** Icon cache not updated.  After (un)install, run this:"; \
			echo "***   $(gtk_update_icon_cache) $(DESTDIR)$(datadir)/icons/$$THEME"; \
		fi \
	done;

install-icons:
	@-for icon in $(public_icons); do \
		THEME=`echo $$icon | cut -d _ -f1`; \
		CONTEXT=`echo $$icon | cut -d _ -f2`; \
		SIZE=`echo $$icon | cut -d _ -f3`; \
		ICONFILE=`echo $$icon | cut -d _ -f4`; \
		mkdir -p $(DESTDIR)$(datadir)/icons/$$THEME/$$SIZE/$$CONTEXT; \
		$(INSTALL_DATA) $(srcdir)/$$icon $(DESTDIR)$(datadir)/icons/$$THEME/$$SIZE/$$CONTEXT/$$ICONFILE; \
	done;

uninstall-icons:
	for icon in $(public_icons); do \
		THEME=`echo $$icon | cut -d _ -f1`; \
		CONTEXT=`echo $$icon | cut -d _ -f2`; \
		SIZE=`echo $$icon | cut -d _ -f3`; \
		ICONFILE=`echo $$icon | cut -d _ -f4`; \
		rm -f $(DESTDIR)$(datadir)/icons/$$THEME/$$SIZE/$$CONTEXT/$$ICONFILE; \
	done;

install-data-local: install-icons update-icon-cache
uninstall-local: uninstall-icons update-icon-cache

EXTRA_DIST = $(public_icons) $(desktop_DATA)

CLEANFILES = $(desktop_DATA)

DISTCLEANFILES = $(desktop_DATA)
