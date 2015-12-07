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

#include "matrix-handles.h"

#define MATRIX_DEBUG_FLAG MATRIX_DEBUG_PARSER
#include "matrix-debug.h"

gboolean
matrix_id_is_valid(const gchar *matrix_id, gboolean strict_mode)
{
    MATRIX_DEBUG(
            "Validating Matrix ID '%s' with strict mode %d",
            matrix_id, strict_mode);

    if (!matrix_id || *matrix_id == '\0') {
        return FALSE;
    }

    if (!g_utf8_validate(matrix_id, -1, NULL)) {
        return FALSE;
    }

    /* TODO: Do the actual validation */

    return TRUE;
}
