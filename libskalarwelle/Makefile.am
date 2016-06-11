AM_CPPFLAGS = \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	$(LIBSKALARWELLE_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

lib_LTLIBRARIES =  \
	libskalarwelle.la

libskalarwelle_la_SOURCES =  \
	libskalarwelle.c \
	Mumble.pb-c.c \
	Mumble.pb-c.h \
	Mumble.proto \
	network.c \
	network.h \
	packet_data_stream.c \
	packet_data_stream.h \
	packet_header.h

libskalarwelle_la_CFLAGS = -std=c11 \
	-Wall \
	-Wextra \
	-pedantic 

libskalarwelle_la_LDFLAGS = 

libskalarwelle_la_LIBADD = $(LIBSKALARWELLE_LIBS)


