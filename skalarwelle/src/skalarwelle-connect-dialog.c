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

#include "skalarwelle-connect-dialog.h"

#include <glib/gi18n.h>

typedef struct _SkalarwelleConnectDialog
{
  GtkDialog parent;

  GtkEntry *host_name_entry;
  GtkEntry *port_entry;
  GtkEntry *user_name_entry;
  GtkButton *ok_button;
  GtkButton *cancel_button;

  gchar *host_name;
  guint port;
  gchar *user_name;
} SkalarwelleConnectDialog;

/* *INDENT-OFF* */
G_DEFINE_TYPE (SkalarwelleConnectDialog, skalarwelle_connect_dialog,
               GTK_TYPE_DIALOG);
/* *INDENT-ON* */

enum
{
  PROP_HOST_NAME = 1,
  PROP_PORT,
  PROP_USER_NAME,
  N_PROPERTIES
};

static GParamSpec *obj_properties[N_PROPERTIES] = { NULL, };

static void
skalarwelle_connect_dialog_set_property (GObject *object,
                                         guint property_id,
                                         const GValue * value,
                                         GParamSpec * pspec)
{
  SkalarwelleConnectDialog *self = SKALARWELLE_CONNECT_DIALOG (object);

  switch (property_id)
    {
    case PROP_HOST_NAME:
      g_free (self->host_name);
      self->host_name = g_value_dup_string (value);
      break;

    case PROP_PORT:
      self->port = g_value_get_uint (value);
      break;

    case PROP_USER_NAME:
      g_free (self->user_name);
      self->user_name = g_value_dup_string (value);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
    }
}

static void
skalarwelle_connect_dialog_get_property (GObject *object,
                                         guint property_id,
                                         GValue * value, GParamSpec * pspec)
{
  SkalarwelleConnectDialog *self = SKALARWELLE_CONNECT_DIALOG (object);

  switch (property_id)
    {
    case PROP_HOST_NAME:
      g_value_set_string (value, self->host_name);
      break;

    case PROP_PORT:
      g_value_set_uint (value, self->port);
      break;

    case PROP_USER_NAME:
      g_value_set_string (value, self->user_name);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
    }
}

static void
skalarwelle_connect_dialog_init (SkalarwelleConnectDialog * dialog)
{
  GtkDialog *dia = GTK_DIALOG (dialog);
  gtk_widget_init_template (GTK_WIDGET (dialog));
  g_object_bind_property (dialog, "host-name", dialog->host_name_entry,
                          "text", G_BINDING_BIDIRECTIONAL);
  g_object_bind_property (dialog, "port", dialog->port_entry, "text",
                          G_BINDING_BIDIRECTIONAL);
  g_object_bind_property (dialog, "user-name", dialog->user_name_entry,
                          "text", G_BINDING_BIDIRECTIONAL);
}

static void
skalarwelle_connect_dialog_finalize (GObject *object)
{
  SkalarwelleConnectDialog *self = SKALARWELLE_CONNECT_DIALOG (object);
  g_free (self->host_name);
  g_free (self->user_name);
  G_OBJECT_CLASS (skalarwelle_connect_dialog_parent_class)->finalize (object);
}

static void
skalarwelle_connect_dialog_class_init (SkalarwelleConnectDialogClass * klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  object_class->finalize = skalarwelle_connect_dialog_finalize;

  const gchar *s =
    "/com/github/promi/skalarwelle/skalarwelle-connect-dialog.ui";
  gtk_widget_class_set_template_from_resource (widget_class, s);
  gtk_widget_class_bind_template_child (widget_class,
                                        SkalarwelleConnectDialog, ok_button);
  gtk_widget_class_bind_template_child (widget_class,
                                        SkalarwelleConnectDialog,
                                        cancel_button);
  gtk_widget_class_bind_template_child (widget_class,
                                        SkalarwelleConnectDialog,
                                        host_name_entry);
  gtk_widget_class_bind_template_child (widget_class,
                                        SkalarwelleConnectDialog, port_entry);
  gtk_widget_class_bind_template_child (widget_class,
                                        SkalarwelleConnectDialog,
                                        user_name_entry);

  object_class->set_property = skalarwelle_connect_dialog_set_property;
  object_class->get_property = skalarwelle_connect_dialog_get_property;

  obj_properties[PROP_HOST_NAME] =
    g_param_spec_string ("host-name",
                         "Host name",
                         "Name of the Mumble server host.",
                         NULL, G_PARAM_READWRITE);

  obj_properties[PROP_PORT] =
    g_param_spec_uint ("port",
                       "Port",
                       "Port of the Mumble server.", 0,
                       65535, 64738, G_PARAM_READWRITE);

  obj_properties[PROP_USER_NAME] =
    g_param_spec_string ("user-name",
                         "User name",
                         "Name of the Mumble user.", NULL, G_PARAM_READWRITE);

  g_object_class_install_properties (object_class,
                                     N_PROPERTIES, obj_properties);
}

SkalarwelleConnectDialog *
skalarwelle_connect_dialog_new (GtkWindow * parent)
{
  SkalarwelleConnectDialog *dialog =
    g_object_new (skalarwelle_connect_dialog_get_type (), NULL);
  GtkWindow *win = GTK_WINDOW (dialog);
  gtk_window_set_transient_for (win, parent);
  gtk_window_set_modal (win, TRUE);
  gtk_window_set_destroy_with_parent (win, TRUE);
  return dialog;
}

/*
void
skalarwelle_connect_dialog_connect_clicked (gpointer user_data,
                                         GtkToolButton *button)
{
  SkalarwelleConnectDialog *self = SKALARWELLE_CONNECT_DIALOG (user_data);
  g_return_if_fail (self != NULL);
  skalarwelle_connect ("localhost", 64738);
}
 */