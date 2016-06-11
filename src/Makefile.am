AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	$(SKALARWELLE_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = skalarwelle

skalarwelle_SOURCES = \
	main.c \
	skalarwelle-application.c \
	skalarwelle-application.h \
	skalarwelle-main-window.c \
	skalarwelle-main-window.h \
	skalarwelle-main-window.ui

skalarwelle_LDFLAGS = \
	-Wl,--export-dynamic

skalarwelle_LDADD = $(SKALARWELLE_LIBS)

nodist_skalarwelle_SOURCES = resources.c

CLEANFILES = resources.c

resources.c: resources.xml skalarwelle-main-window.ui
	glib-compile-resources $(srcdir)/resources.xml --target=$@ \
	--sourcedir=$(srcdir) --c-name skalarwelle --generate-source

# gsettings_SCHEMAS = com.github.promi.cmumble.gschema.xml

# @GSETTINGS_RULES@

uninstall-local:
	-rm -r $(pkgdatadir)
