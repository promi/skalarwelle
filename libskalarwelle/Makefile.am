AUTOMAKE_OPTIONS = subdir-objects

lib_LTLIBRARIES = libskalarwelle-@API_VERSION@.la

libskalarwelle_@API_VERSION@_la_CPPFLAGS = $(LIBSKALARWELLE_CFLAGS)

libskalarwelle_@API_VERSION@_la_LDFLAGS = $(LIBSKALARWELLE_LIBS)

libskalarwelle_@API_VERSION@_la_SOURCES = \
    src/error.c \
    src/error.h \
    src/libskalarwelle.c \
    src/libskalarwelle.h \
    src/Mumble.pb-c.c \
    src/Mumble.pb-c.h \
    src/network.c \
    src/network.h \
    src/packet_data_stream.c \
    src/packet_data_stream.h

libskalarwelle_includedir = $(includedir)/libskalarwelle-@API_VERSION@
libskalarwelle_include_HEADERS = src/libskalarwelle.h

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = skalarwelle-@API_VERSION@.pc

DISTCLEANFILES = $(pkgconfig_DATA)
EXTRA_DIST = skalarwelle.pc.in src/Mumble.proto

