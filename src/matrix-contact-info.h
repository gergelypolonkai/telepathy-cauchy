/*
 * This file is part of telepathy-matrix
 *
 * telepathy-matrix is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version.
 *
 * telepathy-matrix is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with telepathy-matrix. If not, see
 * <http://www.gnu.org/licenses/>.
 */

#ifndef __MATRIX_CONTACT_INFO_H__
#define __MATRIX_CONTACT_INFO_H__

#include <glib.h>
#include <glib-object.h>
#include <telepathy-glib/telepathy-glib.h>

#include "matrix-connection.h"

G_BEGIN_DECLS

void matrix_contact_info_class_init(MatrixConnectionClass *klass);
void matrix_contact_info_iface_init(gpointer g_iface, gpointer iface_data);
void matrix_contact_info_init(MatrixConnection *connection);

G_END_DECLS

#endif /* __MATRIX_CONTACT_INFO_H__ */
