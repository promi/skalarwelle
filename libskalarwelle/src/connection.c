/* -*- Mode: C; indent-tabs-mode: nil; c-basic-offset: 2; tab-width: 8 -*-  */
/*
    skalarwelle - Gtk+ mumble client written in C
    Copyright (C) 2016 Prometheus <prometheus@unterderbruecke.de>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>

#include "connection.h"
#include "network.h"
#include "Mumble.pb-c.h"

typedef struct _SkalarwelleConnection
{
  GObject parent;

  MumbleNetwork *net;
} SkalarwelleConnection;

/* *INDENT-OFF* */
G_DEFINE_TYPE (SkalarwelleConnection, skalarwelle_connection, G_TYPE_OBJECT)
/* *INDENT-ON* */

static void skalarwelle_connection_finalize (GObject *object);

static void
skalarwelle_connection_class_init (SkalarwelleConnectionClass *klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);

  gobject_class->finalize = skalarwelle_connection_finalize;
}

static void
skalarwelle_connection_init (SkalarwelleConnection *self)
{
}

static void
skalarwelle_connection_finalize (GObject *object)
{
  SkalarwelleConnection *self = SKALARWELLE_CONNECTION (object);

  GObjectClass *parent_class =
    G_OBJECT_CLASS (skalarwelle_connection_parent_class);
  (*parent_class->finalize) (object);
}

SkalarwelleConnection *
skalarwelle_connection_new ()
{
  return g_object_new (SKALARWELLE_TYPE_CONNECTION, NULL);
}

void
skalarwelle_connection_send_our_version (MumbleNetwork *net, GError **err)
{
  g_return_if_fail (net != NULL);
  g_return_if_fail (err == NULL || *err == NULL);

  MumbleProto__Version message = MUMBLE_PROTO__VERSION__INIT;
  message.has_version = 1;
  message.version = 0x00010300;
  message.release = "libskalarwelle (git)";
  message.os = "Unknown";
  message.os_version = "Unknown";

  MUMBLE_NETWORK_WRITE_PACKET (net, VERSION, version, &message, err);
}

void
skalarwelle_connection_send_authenticate (MumbleNetwork *net,
                                          const gchar *username, GError **err)
{
  g_return_if_fail (net != NULL);
  g_return_if_fail (username != NULL);
  g_return_if_fail (err == NULL || *err == NULL);

  MumbleProto__Authenticate message = MUMBLE_PROTO__AUTHENTICATE__INIT;
  message.username = (gchar *) username;
  message.password = "";
  message.n_tokens = 0;
  message.tokens = NULL;
  message.n_celt_versions = 0;
  message.celt_versions = NULL;
  message.has_opus = 1;
  message.opus = 1;

  MUMBLE_NETWORK_WRITE_PACKET (net, AUTHENTICATE, authenticate, &message,
                               err);
}

void
skalarwelle_connection_send_ping (MumbleNetwork *net, GError **err)
{
  g_return_if_fail (net != NULL);
  g_return_if_fail (err == NULL || *err == NULL);

  MumbleProto__Ping message = MUMBLE_PROTO__PING__INIT;
  // message.has_timestamp = 1;

  MUMBLE_NETWORK_WRITE_PACKET (net, PING, ping, &message, err);
}

gboolean
skalarwelle_connection_read_message (MumbleNetwork *net,
                                     MumbleMessageType type, guint8 *data,
                                     guint32 length, gpointer user_data)
{
  g_return_val_if_fail (net != NULL, FALSE);
  g_return_val_if_fail (user_data != NULL, FALSE);
  SkalarwelleConnection *self = SKALARWELLE_CONNECTION (user_data);
  // Payload could be empty (i.e. PING message without any actual data filled)
  // That's not an error
  if (data == NULL)
    {
      return TRUE;
    }
  g_return_val_if_fail (length != 0, FALSE);

  if (type == MUMBLE_MESSAGE_TYPE__VERSION)
    {
      MumbleProto__Version *message =
        mumble_proto__version__unpack (NULL, length, data);
      printf ("\nreceived version message\n");
      if (message->has_version == 1)
        {
          printf ("version = %x\n", message->version);
        }
      printf ("release = %s\n", message->release);
      printf ("os = %s\n", message->os);
      printf ("os_version = %s\n", message->os_version);
      printf ("\n");
      mumble_proto__version__free_unpacked (message, NULL);
    }
  else if (type == MUMBLE_MESSAGE_TYPE__UDP_TUNNEL)
    {
      // read_audio_data (self, data, length);
    }
  else if (type == MUMBLE_MESSAGE_TYPE__REJECT)
    {
      MumbleProto__Reject *message =
        mumble_proto__reject__unpack (NULL, length, data);
      printf ("\nreceived reject message\n");
      if (message->has_type == 1)
        {
          printf ("type = %d\n", message->type);
        }
      printf ("reason = %s\n", message->reason);
      printf ("\n");
      mumble_proto__reject__free_unpacked (message, NULL);
      g_free (data);
      return FALSE;
    }
  else
    {
      // printf ("%d[%d] ", type, length);
    }

  g_free (data);
  return TRUE;
}

gboolean
skalarwelle_connection_timeout (gpointer user_data)
{
  // printf ("PING\n");
  MumbleNetwork *net = MUMBLE_NETWORK (user_data);
  GError *err = NULL;
  skalarwelle_connection_send_ping (net, &err);
  if (err != NULL)
    {
      fprintf (stderr,
               "could not send PING packet to the server: %s\n",
               err->message);
      return FALSE;
    }
  return TRUE;
}

gboolean
skalarwelle_connection_connect (SkalarwelleConnection *self,
                                const gchar *host_name, guint16 port,
                                const char *user_name)
{
  g_return_if_fail (host_name != NULL);
  g_return_if_fail (user_name != NULL);
  printf ("Connect clicked: host_name = '%s', port = %d, user_name = '%s'\n",
          host_name, port, user_name);
  self->net = mumble_network_new ();
  GError *err = NULL;
  mumble_network_connect (self->net, host_name, port, NULL, &err);
  if (err != NULL)
    {
      fprintf (stderr, "Could not connect to the server '%s:%d': '%s'\n",
               host_name, port, err->message);
      goto fail_cleanup;
    }

  skalarwelle_connection_send_our_version (self->net, &err);
  if (err != NULL)
    {
      fprintf (stderr, "Could not send our version to the server: '%s'\n",
               err->message);
      goto fail_cleanup;
    }

  skalarwelle_connection_send_authenticate (self->net, user_name, &err);
  if (err != NULL)
    {
      fprintf (stderr,
               "Could not send authenticate to the server : '%s'\n",
               err->message);
      goto fail_cleanup;
    }

  mumble_network_read_packet_async (self->net,
                                    &skalarwelle_connection_read_message,
                                    self, &err);
  if (err != NULL)
    {
      fprintf (stderr,
               "Could not start reading from server : '%s'\n", err->message);
      goto fail_cleanup;
    }

  g_timeout_add_seconds (20, skalarwelle_connection_timeout, self->net);
  goto finally;

fail_cleanup:
  g_error_free (err);

finally:
  return;
}
