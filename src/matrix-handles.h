/*
 * This file is part of telepathy-matrix
 *
 * telepathy-matrix is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version.
 *
 * telepathy-matrix is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License * along with telepathy-matrix. If not, see
 * <http://www.gnu.org/licenses/>.
 */

#ifndef __MATRIX_HANDLES_H__
#define __MATRIX_HANDLES_H__

#include <glib.h>

gboolean matrix_id_is_valid(const gchar *matrix_id, gboolean strict_mode);
gchar *matrix_normalize_id(const gchar *id, GError **err);

#endif /* __MATRIX_HANDLES_H__ */
