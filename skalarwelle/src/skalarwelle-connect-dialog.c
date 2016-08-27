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
  GtkButton *ok_button;
  GtkButton *cancel_button;
} SkalarwelleConnectDialog;

/* *INDENT-OFF* */
G_DEFINE_TYPE (SkalarwelleConnectDialog, skalarwelle_connect_dialog,
               GTK_TYPE_DIALOG);
/* *INDENT-ON* */

static void
skalarwelle_connect_dialog_init (SkalarwelleConnectDialog * dialog)
{
  GtkDialog *dia = GTK_DIALOG (dialog);
  gtk_widget_init_template (GTK_WIDGET (dialog));
}

static void
skalarwelle_connect_dialog_finalize (GObject *object)
{
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
