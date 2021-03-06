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

#include "main-window.h"

#include <glib/gi18n.h>

typedef struct _SkalarwelleMainWindow
{
  GtkApplicationWindow parent;

  GtkNotebook *notebook;
  GSettings *set;
} SkalarwelleMainWindow;

/* *INDENT-OFF* */
G_DEFINE_TYPE (SkalarwelleMainWindow, skalarwelle_main_window,
               GTK_TYPE_APPLICATION_WINDOW)
/* *INDENT-ON* */

static void
skalarwelle_main_window_init (SkalarwelleMainWindow *self)
{
  self->set = g_settings_new (APPLICATION_ID);
  g_return_if_fail (self->set != NULL);
  gtk_widget_init_template (GTK_WIDGET (self));
}

static void
skalarwelle_main_window_finalize (GObject *object)
{
  SkalarwelleMainWindow *self = SKALARWELLE_MAIN_WINDOW (object);
  g_object_unref (self->set);

  G_OBJECT_CLASS (skalarwelle_main_window_parent_class)->finalize (object);
}

static void
skalarwelle_main_window_class_init (SkalarwelleMainWindowClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  object_class->finalize = skalarwelle_main_window_finalize;

  const gchar *s = "/com/github/promi/skalarwelle/main-window.ui";
  gtk_widget_class_set_template_from_resource (widget_class, s);
  gtk_widget_class_bind_template_callback (widget_class,
                                           skalarwelle_main_window_connect_clicked);
  gtk_widget_class_bind_template_child (widget_class, SkalarwelleMainWindow,
                                        notebook);
}

void
skalarwelle_main_window_connect (SkalarwelleMainWindow *self,
                                 const gchar *host_name, guint16 port,
                                 const char *user_name);

SkalarwelleMainWindow *
skalarwelle_main_window_new (void)
{
  SkalarwelleMainWindow *self =
    g_object_new (skalarwelle_main_window_get_type (), NULL);

  gchar *host_name = g_settings_get_string (self->set, "mumble-host");
  guint16 port = g_settings_get_int (self->set, "mumble-port");
  gchar *user_name = g_settings_get_string (self->set, "mumble-user");
  skalarwelle_main_window_connect (self, host_name, port, user_name);
  return self;
}

void
skalarwelle_main_window_connect (SkalarwelleMainWindow *self,
                                 const gchar *host_name, guint16 port,
                                 const char *user_name)
{
  SkalarwelleConnection *connection = skalarwelle_connection_new ();
  if (skalarwelle_connection_connect (connection, host_name, port, user_name))
    {
      const size_t label_max_length = 100;
      gchar label_text[label_max_length];
      snprintf (label_text, label_max_length, "%s:%d (%s)", host_name, port,
                user_name);
      GtkWidget *label = gtk_label_new (label_text);
      GtkWidget *treeview = gtk_tree_view_new ();
      gtk_notebook_append_page (self->notebook, treeview, label);
      gtk_widget_show_all (treeview);
      gtk_widget_show_all (label);
      // g_object_unref (connection);
    }
  else
    {
      g_object_unref (connection);
    }
}

void
skalarwelle_main_window_connect_clicked (gpointer user_data,
                                         G_GNUC_UNUSED GtkToolButton *button)
{
  SkalarwelleMainWindow *self = SKALARWELLE_MAIN_WINDOW (user_data);
  g_return_if_fail (self != NULL);

  SkalarwelleConnectDialog *dialog =
    skalarwelle_connect_dialog_new (GTK_WINDOW (self));
  GtkWidget *wid = GTK_WIDGET (dialog);
  GObject *obj = G_OBJECT (dialog);

  GValue host_name = G_VALUE_INIT;
  g_value_init (&host_name, G_TYPE_STRING);
  g_value_set_string (&host_name, "localhost");
  g_object_set_property (obj, "host-name", &host_name);

  GValue port = G_VALUE_INIT;
  g_value_init (&port, G_TYPE_UINT);
  g_value_set_uint (&port, 64738);
  g_object_set_property (obj, "port", &port);

  GValue user_name = G_VALUE_INIT;
  g_value_init (&user_name, G_TYPE_STRING);
  g_value_set_string (&user_name, "");
  g_object_set_property (obj, "user-name", &user_name);

  gtk_widget_show_all (wid);
  gint result = gtk_dialog_run (GTK_DIALOG (dialog));
  switch (result)
    {
    case GTK_RESPONSE_OK:
      g_object_get_property (obj, "host-name", &host_name);
      g_object_get_property (obj, "port", &port);
      g_object_get_property (obj, "user-name", &user_name);
      skalarwelle_main_window_connect (self, g_value_get_string (&host_name),
                                       (guint16) g_value_get_uint (&port),
                                       g_value_get_string (&user_name));
      break;
    default:
      break;
    }

  g_value_unset (&host_name);
  g_value_unset (&port);
  g_value_unset (&user_name);
  gtk_widget_destroy (wid);
}
