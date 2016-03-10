/*
 * This file is part of telepathy-cauchy
 *
 * telepathy-cauchy is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version.
 *
 * telepathy-cauchy is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with telepathy-cauchy. If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include "cauchy-handles.h"

#include <telepathy-glib/telepathy-glib.h>

#define CAUCHY_DEBUG_FLAG CAUCHY_DEBUG_PARSER
#include "cauchy-debug.h"

gboolean
cauchy_id_is_valid(const gchar *cauchy_id, gboolean strict_mode)
{
    CAUCHY_DEBUG(
            "Validating Cauchy ID '%s' with strict mode %d",
            cauchy_id, strict_mode);

    if (!cauchy_id || *cauchy_id == '\0') {
        return FALSE;
    }

    if (!g_utf8_validate(cauchy_id, -1, NULL)) {
        return FALSE;
    }

    /* TODO: Do the actual validation */

    return TRUE;
}

gchar *
cauchy_normalize_id(const gchar *id, GError **err)
{
    if (!cauchy_id_is_valid(id, FALSE)) {
        g_set_error(err,
                    TP_ERROR, TP_ERROR_INVALID_HANDLE,
                    "Invalid Cauchy ID");

        return NULL;
    }

    /* telepathy-idle sets the nickname to lowercase here. I’m not
     * sure it can be done with Cauchy IDs. TODO: check if it can.
     */
    return g_strdup(id);
}
