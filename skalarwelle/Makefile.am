AUTOMAKE_OPTIONS = subdir-objects

bin_PROGRAMS = skalarwelle

skalarwelle_SOURCES = src/main.c \
	src/resources.xml \
	src/application.c \
	src/application.h \
	src/main-window.c \
	src/main-window.h \
	src/main-window.ui \
	src/connect-dialog.c \
	src/connect-dialog.h \
	src/connect-dialog.ui

AM_CPPFLAGS = -Wall -pedantic -std=c11 -Wextra \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	$(SKALARWELLE_CFLAGS)

# skalarwelle_CPPFLAGS = $(SKALARWELLE_CFLAGS)

skalarwelle_LDFLAGS = $(SKALARWELLE_LIBS)

nodist_skalarwelle_SOURCES = src/resources.c

CLEANFILES = src/resources.c

src/resources.c: src/resources.xml src/main-window.ui \
src/connect-dialog.ui
	glib-compile-resources $(srcdir)/src/resources.xml --target=$@ \
	--sourcedir=$(srcdir)/src --c-name skalarwelle --generate-source

gsettings_SCHEMAS = src/com.github.promi.cmumble.gschema.xml

@GSETTINGS_RULES@

uninstall-local:
	-rm -r $(pkgdatadir)
