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

#ifndef _SKALARWELLE_APPLICATION_H_
#define _SKALARWELLE_APPLICATION_H_

#include <gtk/gtk.h>

/* *INDENT-OFF* */
G_BEGIN_DECLS
#define SKALARWELLE_TYPE_APPLICATION skalarwelle_application_get_type ()
G_DECLARE_FINAL_TYPE (SkalarwelleApplication, skalarwelle_application,
                      SKALARWELLE, APPLICATION, GtkApplication)
/* *INDENT-ON* */

SkalarwelleApplication *skalarwelle_application_new (void);

G_END_DECLS
#endif /* _SKALARWELLE_APPLICATION_H_ */
