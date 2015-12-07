/*
 * This file is part of telepathy-matrix.
 *
 * telepathy-matrix is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * telepathy-matrix is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with telepathy-matrix.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#ifndef __MATRIX_DEBUG_H__
#define __MATRIX_DEBUG_H__

#include <glib.h>

typedef enum {
    MATRIX_DEBUG_CONNECTION = (1 << 0),
    MATRIX_DEBUG_DNS = (1 << 1),
    MATRIX_DEBUG_IM = (1 << 2),
    MATRIX_DEBUG_MUC = (1 << 3),
    MATRIX_DEBUG_NETWORK = (1 << 4),
    MATRIX_DEBUG_PARSER = (1 << 5),
    MATRIX_DEBUG_TEXT = (1 << 6),
    MATRIX_DEBUG_ROOMLIST = (1 << 7),
    MATRIX_DEBUG_TLS = (1 << 8),
} MatrixDebugFlags;

void matrix_debug_init (void);
void matrix_debug(MatrixDebugFlags flag, const gchar *format, ...) G_GNUC_PRINTF(2, 3);

void matrix_debug_free (void);

#endif /* __MATRIX_DEBUG_H__ */

#ifdef MATRIX_DEBUG_FLAG
# undef MATRIX_DEBUG
# define MATRIX_DEBUG(format, ...) \
    matrix_debug(MATRIX_DEBUG_FLAG, "%s: " format, G_STRFUNC, ##__VA_ARGS__)
#endif /* MATRIX_DEBUG_FLAG */
