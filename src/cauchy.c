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

#include <config.h>

#include <telepathy-glib/telepathy-glib.h>

#include "cauchy-connection-manager.h"
#include "cauchy-debug.h"

static TpBaseConnectionManager *
_construct_cm(void)
{
    TpBaseConnectionManager *base_cm = TP_BASE_CONNECTION_MANAGER(
            g_object_new(CAUCHY_TYPE_CONNECTION_MANAGER, NULL));

    return base_cm;
}

int
main(int argc, char **argv)
{
    TpDebugSender *debug_sender;
    int result;

    g_type_init();
    tp_debug_divert_messages(g_getenv("CAUCHY_LOGFILE"));

    cauchy_debug_init();

    debug_sender = tp_debug_sender_dup();

    result = tp_run_connection_manager(
            "telepathy-cauchy", VERSION,
            _construct_cm,
            argc, argv);

    g_object_unref (debug_sender);

    return result;
}
