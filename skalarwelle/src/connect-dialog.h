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

#ifndef _SKALARWELLE_CONNECT_DIALOG_H_
#define _SKALARWELLE_CONNECT_DIALOG_H_

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <glib-object.h>
#include <gtk/gtk.h>

/* *INDENT-OFF* */
G_BEGIN_DECLS
#define SKALARWELLE_TYPE_CONNECT_DIALOG skalarwelle_connect_dialog_get_type ()
G_DECLARE_FINAL_TYPE (SkalarwelleConnectDialog, skalarwelle_connect_dialog,
                      SKALARWELLE, CONNECT_DIALOG, GtkDialog)
/* *INDENT-ON* */

SkalarwelleConnectDialog *skalarwelle_connect_dialog_new (GtkWindow * parent);

G_END_DECLS
#endif /* _SKALARWELLE_CONNECT_DIALOG_H_ */
