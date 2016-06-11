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

#ifndef _SKALARWELLE_
#define _SKALARWELLE_

#include <gtk/gtk.h>

G_BEGIN_DECLS
#define SKALARWELLE_TYPE_APPLICATION             (skalarwelle_get_type ())
#define SKALARWELLE_APPLICATION(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), SKALARWELLE_TYPE_APPLICATION, Skalarwelle))
#define SKALARWELLE_APPLICATION_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), SKALARWELLE_TYPE_APPLICATION, SkalarwelleClass))
#define SKALARWELLE_IS_APPLICATION(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), SKALARWELLE_TYPE_APPLICATION))
#define SKALARWELLE_IS_APPLICATION_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), SKALARWELLE_TYPE_APPLICATION))
#define SKALARWELLE_APPLICATION_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), SKALARWELLE_TYPE_APPLICATION, SkalarwelleClass))
typedef struct _SkalarwelleClass SkalarwelleClass;
typedef struct _Skalarwelle Skalarwelle;
typedef struct _SkalarwellePrivate SkalarwellePrivate;

struct _SkalarwelleClass
{
  GtkApplicationClass parent_class;
};

struct _Skalarwelle
{
  GtkApplication parent_instance;
  SkalarwellePrivate *priv;
};

GType
skalarwelle_get_type (void);
  
Skalarwelle*
skalarwelle_new (void);

G_END_DECLS
#endif /* _APPLICATION_H_ */
