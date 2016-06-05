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
#include "skalarwelle.h"

#include <glib/gi18n.h>



/* For testing propose use the local (not installed) ui file */
/* #define UI_FILE PACKAGE_DATA_DIR"/ui/skalarwelle.ui" */
#define UI_FILE "src/skalarwelle.ui"
#define TOP_WINDOW "window"


G_DEFINE_TYPE (Skalarwelle, skalarwelle, GTK_TYPE_APPLICATION);

/* ANJUTA: Macro SKALARWELLE_APPLICATION gets Skalarwelle - DO NOT REMOVE */
struct _SkalarwellePrivate
{
  /* ANJUTA: Widgets declaration for skalarwelle.ui - DO NOT REMOVE */
};

/* Create a new window loading a file */
static void
skalarwelle_new_window (GApplication *app, GFile * file)
{
  GtkWidget *window;

  GtkBuilder *builder;
  GError *error = NULL;

  SkalarwellePrivate *priv = SKALARWELLE_APPLICATION (app)->priv;

  /* Load UI from file */
  builder = gtk_builder_new ();
  if (!gtk_builder_add_from_file (builder, UI_FILE, &error))
    {
      g_critical ("Couldn't load builder file: %s", error->message);
      g_error_free (error);
    }

  /* Auto-connect signal handlers */
  gtk_builder_connect_signals (builder, app);

  /* Get the window object from the ui file */
  window = GTK_WIDGET (gtk_builder_get_object (builder, TOP_WINDOW));
  if (!window)
    {
      g_critical ("Widget \"%s\" is missing in file %s.",
                  TOP_WINDOW, UI_FILE);
    }


  /* ANJUTA: Widgets initialization for skalarwelle.ui - DO NOT REMOVE */

  g_object_unref (builder);


  gtk_window_set_application (GTK_WINDOW (window), GTK_APPLICATION (app));
  if (file != NULL)
    {
      /* TODO: Add code here to open the file in the new window */
    }

  gtk_widget_show_all (GTK_WIDGET (window));
}


/* GApplication implementation */
static void
skalarwelle_activate (GApplication *application)
{
  skalarwelle_new_window (application, NULL);
}

static void
skalarwelle_open (GApplication *application,
                  GFile ** files, gint n_files, const gchar *hint)
{
  gint i;

  for (i = 0; i < n_files; i++)
    skalarwelle_new_window (application, files[i]);
}

static void
skalarwelle_init (Skalarwelle * object)
{
  object->priv =
    G_TYPE_INSTANCE_GET_PRIVATE (object, SKALARWELLE_TYPE_APPLICATION,
                                 SkalarwellePrivate);
}

static void
skalarwelle_finalize (GObject *object)
{
  G_OBJECT_CLASS (skalarwelle_parent_class)->finalize (object);
}

static void
skalarwelle_class_init (SkalarwelleClass * klass)
{
  G_APPLICATION_CLASS (klass)->activate = skalarwelle_activate;
  G_APPLICATION_CLASS (klass)->open = skalarwelle_open;

  g_type_class_add_private (klass, sizeof (SkalarwellePrivate));

  G_OBJECT_CLASS (klass)->finalize = skalarwelle_finalize;
}

Skalarwelle *
skalarwelle_new (void)
{
  return g_object_new (skalarwelle_get_type (),
                       "application-id", "org.gnome.skalarwelle",
                       "flags", G_APPLICATION_HANDLES_OPEN, NULL);
}
