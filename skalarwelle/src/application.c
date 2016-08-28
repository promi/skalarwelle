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
#include <glib/gi18n.h>

#include "application.h"
#include "main-window.h"

typedef struct _SkalarwelleApplication
{
  GtkApplication parent;
} SkalarwelleApplication;

/* *INDENT-OFF* */
G_DEFINE_TYPE (SkalarwelleApplication, skalarwelle_application,
               GTK_TYPE_APPLICATION)
/* *INDENT-ON* */

static void
skalarwelle_application_new_window (GApplication *app,
                                    G_GNUC_UNUSED GFile *file)
{
  SkalarwelleMainWindow *win = skalarwelle_main_window_new ();
  gtk_window_set_application (GTK_WINDOW (win), GTK_APPLICATION (app));
  gtk_widget_show_all (GTK_WIDGET (win));
}

static void
skalarwelle_application_activate (GApplication *application)
{
  skalarwelle_application_new_window (application, NULL);
}

static void
skalarwelle_application_open (GApplication *application,
                              G_GNUC_UNUSED GFile **files,
                              G_GNUC_UNUSED gint n_files,
                              G_GNUC_UNUSED const gchar *hint)
{
  skalarwelle_application_new_window (application, NULL);
}

static void
skalarwelle_application_init (G_GNUC_UNUSED SkalarwelleApplication *object)
{
}

static void
skalarwelle_application_finalize (GObject *object)
{
  G_OBJECT_CLASS (skalarwelle_application_parent_class)->finalize (object);
}

static void
skalarwelle_application_class_init (SkalarwelleApplicationClass *klass)
{
  G_APPLICATION_CLASS (klass)->activate = skalarwelle_application_activate;
  G_APPLICATION_CLASS (klass)->open = skalarwelle_application_open;

  G_OBJECT_CLASS (klass)->finalize = skalarwelle_application_finalize;
}

SkalarwelleApplication *
skalarwelle_application_new (void)
{
  return g_object_new (skalarwelle_application_get_type (),
                       "application-id", "com.github.promi.skalarwelle",
                       "flags", G_APPLICATION_HANDLES_OPEN, NULL);
}
