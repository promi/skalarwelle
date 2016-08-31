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


#include "connection.h"

typedef struct _SkalarwelleConnection
{
  GObject parent;
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

  GObjectClass *parent_class = G_OBJECT_CLASS (skalarwelle_connection_parent_class);
  (*parent_class->finalize) (object);
}

SkalarwelleConnection *
skalarwelle_connection_new ()
{
  return g_object_new (SKALARWELLE_TYPE_CONNECTION, NULL);
}

gboolean
skalarwelle_connection_connect (SkalarwelleConnection * self,
                                const gchar *host_name, guint16 port,
                                const char *user_name)
{
  g_return_if_fail (host_name != NULL);
  g_return_if_fail (user_name != NULL);
  printf ("Connect clicked: host_name = '%s', port = %d, user_name = '%s'\n",
          host_name, port, user_name);
}
