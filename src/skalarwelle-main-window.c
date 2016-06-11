/* -*- Mode: C; indent-tabs-mode: nil; c-basic-offset: 2; tab-width: 2 -*-  */
/*
 * skalarwelle-main-window.c
 * Copyright (C) 2016 Unknown <prometheus@unterderbruecke.de>
 *
 * skalarwelle is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * skalarwelle is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "skalarwelle-main-window.h"

struct _SkalarwelleMainWindowPrivate
{
};

G_DEFINE_TYPE (SkalarwelleMainWindow, skalarwelle_main_window, G_TYPE_OBJECT);

static void
skalarwelle_main_window_init (SkalarwelleMainWindow *skalarwelle_main_window)
{
  skalarwelle_main_window->priv = G_TYPE_INSTANCE_GET_PRIVATE (skalarwelle_main_window, SKALARWELLE_TYPE_MAIN_WINDOW, SkalarwelleMainWindowPrivate);
}

static void
skalarwelle_main_window_finalize (GObject *object)
{
  G_OBJECT_CLASS (skalarwelle_main_window_parent_class)->finalize (object);
}

static void
skalarwelle_main_window_class_init (SkalarwelleMainWindowClass *klass)
{
  GObjectClass* object_class = G_OBJECT_CLASS (klass);
  GtkWidgetClass* widget_class = GTK_WIDGET_CLASS (klass);

  g_type_class_add_private (klass, sizeof (SkalarwelleMainWindowPrivate));

  object_class->finalize = skalarwelle_main_window_finalize;

  gtk_widget_class_set_template_from_resource (widget_class, "/com/github/promi/skalarwelle/skalarwelle_main_window.ui");
}

SkalarwelleMainWindow *
skalarwelle_main_window_new (void)
{
  return g_object_new (skalarwelle_main_window_get_type (), NULL);
}

#define UI_FILE "src/skalarwelle.ui"
#define TOP_WINDOW "main_window"

void
skalarwelle_main_window_set_app (SkalarwelleMainWindow *self,
                                 GApplication *app)
{
  g_return_if_fail (self != NULL);
  g_return_if_fail (app != NULL);
  
  GtkBuilder *builder = gtk_builder_new ();
  GError *error = NULL;
  if (!gtk_builder_add_from_file (builder, UI_FILE, &error))
    {
      g_critical ("Couldn't load builder file: %s", error->message);
      g_error_free (error);
    }

  gtk_builder_connect_signals (builder, self);
  GtkApplicationWindow *window = GTK_APPLICATION_WINDOW (gtk_builder_get_object (builder, TOP_WINDOW));
  if (!window)
    {
      g_critical ("Widget \"%s\" is missing in file %s.",
                  TOP_WINDOW, UI_FILE);
    }

  g_object_unref (builder);

  gtk_window_set_application (GTK_WINDOW (window), GTK_APPLICATION (app));
  gtk_widget_show_all (GTK_WIDGET (window));
}

void
skalarwelle_main_window_connect_clicked (gpointer user_data, GtkToolButton *button)
{
  SkalarwelleMainWindow *self = SKALARWELLE_MAIN_WINDOW(user_data);
  printf ("Connect clicked\n");
}
