m4_define([api_version],[0])

AC_INIT([libskalarwelle], 0.1)

AM_INIT_AUTOMAKE([foreign])

AM_SILENT_RULES([yes])

AC_PROG_CC

LT_INIT

dnl glib-2.0 gobject-2.0 gio-2.0 libprotobuf-c opus vorbis vorbisenc shout

AX_PKG_CHECK_MODULES(
	LIBSKALARWELLE,
	[],
	[glib-2.0 libprotobuf-c]
)

AC_SUBST([API_VERSION],api_version)

AC_CONFIG_FILES([
Makefile skalarwelle-$API_VERSION.pc:skalarwelle.pc.in
],[],
[API_VERSION='$API_VERSION'])

AC_OUTPUT
