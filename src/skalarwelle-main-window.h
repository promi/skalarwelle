/* -*- Mode: C; indent-tabs-mode: nil; c-basic-offset: 2; tab-width: 2 -*-  */
/*
 * skalarwelle-main-window.h
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

#ifndef _SKALARWELLE_MAIN_WINDOW_H_
#define _SKALARWELLE_MAIN_WINDOW_H_

#include <glib-object.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS

#define SKALARWELLE_TYPE_MAIN_WINDOW             (skalarwelle_main_window_get_type ())
#define SKALARWELLE_MAIN_WINDOW(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), SKALARWELLE_TYPE_MAIN_WINDOW, SkalarwelleMainWindow))
#define SKALARWELLE_MAIN_WINDOW_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), SKALARWELLE_TYPE_MAIN_WINDOW, SkalarwelleMainWindowClass))
#define SKALARWELLE_IS_MAIN_WINDOW(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), SKALARWELLE_TYPE_MAIN_WINDOW))
#define SKALARWELLE_IS_MAIN_WINDOW_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), SKALARWELLE_TYPE_MAIN_WINDOW))
#define SKALARWELLE_MAIN_WINDOW_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), SKALARWELLE_TYPE_MAIN_WINDOW, SkalarwelleMainWindowClass))

typedef struct _SkalarwelleMainWindowClass SkalarwelleMainWindowClass;
typedef struct _SkalarwelleMainWindow SkalarwelleMainWindow;
typedef struct _SkalarwelleMainWindowPrivate SkalarwelleMainWindowPrivate;


struct _SkalarwelleMainWindowClass
{
  GObjectClass parent_class;
};

struct _SkalarwelleMainWindow
{
  GObject parent_instance;

  SkalarwelleMainWindowPrivate *priv;
};

GType
skalarwelle_main_window_get_type (void);

SkalarwelleMainWindow*
skalarwelle_main_window_new (void);

void
skalarwelle_main_window_set_app (SkalarwelleMainWindow *self,
                                 GApplication *app);

void
skalarwelle_main_window_connect_clicked (gpointer user_data, GtkToolButton *button);

G_END_DECLS

#endif /* _SKALARWELLE_MAIN_WINDOW_H_ */

