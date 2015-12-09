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

#include <config.h>

#include <telepathy-glib/telepathy-glib.h>

#include "matrix-connection-manager.h"
#include "matrix-debug.h"

static TpBaseConnectionManager *
_construct_cm(void)
{
    TpBaseConnectionManager *base_cm = TP_BASE_CONNECTION_MANAGER(
            g_object_new(MATRIX_TYPE_CONNECTION_MANAGER, NULL));

    return base_cm;
}

int
main(int argc, char **argv)
{
    TpDebugSender *debug_sender;
    int result;

    g_type_init();
    tp_debug_divert_messages(g_getenv("MATRIX_LOGFILE"));

    matrix_debug_init();

    debug_sender = tp_debug_sender_dup();

    result = tp_run_connection_manager(
            "telepathy-matrix", VERSION,
            _construct_cm,
            argc, argv);

    g_object_unref (debug_sender);

    return result;
}
