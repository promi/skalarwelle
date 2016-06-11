AC_INIT(skalarwelle, 0.1)
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([1.11])
AM_SILENT_RULES([yes])
AC_PROG_CC
IT_PROG_INTLTOOL([0.35.0])

GETTEXT_PACKAGE=skalarwelle
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE", [GETTEXT package name])
AM_GLIB_GNU_GETTEXT

LT_INIT

PKG_CHECK_MODULES(SKALARWELLE, [gtk+-3.0 >= 2.90.3 ])

PKG_CHECK_MODULES(LIBSKALARWELLE, [glib-2.0 gobject-2.0 gio-2.0 libprotobuf-c 
	opus vorbis vorbisenc shout])

dnl GLIB_GSETTINGS

AC_OUTPUT([
Makefile
libskalarwelle/Makefile
src/Makefile
po/Makefile.in
])
