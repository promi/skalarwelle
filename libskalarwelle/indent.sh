#!/bin/sh
indent \
-T gchar \
-T gfloat \
-T gint \
-T guint \
-T guint16 \
-T guint32 \
-T guint8 \
-T ogg_stream_state \
-T shout_t \
-T vorbis_block \
-T vorbis_comment \
-T vorbis_dsp_state \
-T vorbis_info \
-T GApplication \
-T GApplicationClass \
-T GAsyncResult \
-T GError \
-T GIOStream \
-T GNetworkAddress \
-T GObject \
-T GObjectClass \
-T GQueue \
-T GSocketClient \
-T GSocketClientEvent \
-T GSocketConnectable \
-T GTlsCertificate \
-T GTlsConnection \
-T MumbleApplication \
-T MumbleApplicationClass \
-T MumbleNetwork \
-T MumbleNetworkClass \
-T MumblePacketHeader \
-T OpusDecoder \
-nut "$@"
