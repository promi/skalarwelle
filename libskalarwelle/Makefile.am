AUTOMAKE_OPTIONS = subdir-objects

AM_CPPFLAGS = -Wall -pedantic -std=c11 -Wextra

lib_LTLIBRARIES = libskalarwelle-@API_VERSION@.la

libskalarwelle_@API_VERSION@_la_CPPFLAGS = $(LIBSKALARWELLE_CFLAGS)

libskalarwelle_@API_VERSION@_la_LDFLAGS = $(LIBSKALARWELLE_LIBS)

libskalarwelle_@API_VERSION@_la_SOURCES = \
    src/connection.c \
    src/connection.h \
    src/error.c \
    src/error.h \
    src/Mumble.pb-c.c \
    src/Mumble.pb-c.h \
    src/network.c \
    src/network.h \
    src/packet_data_stream.c \
    src/packet_data_stream.h

libskalarwelle_includedir = $(includedir)/skalarwelle-@API_VERSION@/skalarwelle
libskalarwelle_include_HEADERS = src/connection.h

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = skalarwelle-@API_VERSION@.pc

DISTCLEANFILES = $(pkgconfig_DATA)
EXTRA_DIST = skalarwelle.pc.in src/Mumble.proto

