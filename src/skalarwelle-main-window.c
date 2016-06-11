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

#include "skalarwelle-main-window.h"

#include <glib/gi18n.h>

typedef struct _SkalarwelleMainWindow
{
  GtkApplicationWindow parent;
} SkalarwelleMainWindow;

/* *INDENT-OFF* */
G_DEFINE_TYPE (SkalarwelleMainWindow, skalarwelle_main_window, 
               GTK_TYPE_APPLICATION_WINDOW);
/* *INDENT-ON* */

static void
skalarwelle_main_window_init (SkalarwelleMainWindow *skalarwelle_main_window)
{
  gtk_widget_init_template (GTK_WIDGET (skalarwelle_main_window));
}

static void
skalarwelle_main_window_finalize (GObject *object)
{
  G_OBJECT_CLASS (skalarwelle_main_window_parent_class)->finalize (object);
}

static void
skalarwelle_main_window_class_init (SkalarwelleMainWindowClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  object_class->finalize = skalarwelle_main_window_finalize;

  const gchar *s = "/com/github/promi/skalarwelle/skalarwelle-main-window.ui";
  gtk_widget_class_set_template_from_resource (widget_class, s);
  gtk_widget_class_bind_template_callback (widget_class,
                                           skalarwelle_main_window_connect_clicked);
}

SkalarwelleMainWindow *
skalarwelle_main_window_new (void)
{
  return g_object_new (skalarwelle_main_window_get_type (), NULL);
}

void
skalarwelle_main_window_connect_clicked (gpointer user_data,
                                         GtkToolButton *button)
{
  SkalarwelleMainWindow *self = SKALARWELLE_MAIN_WINDOW (user_data);
  g_return_if_fail (self != NULL);
  printf (_("Connect clicked\n"));
}
