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

#include "cauchy.h"
#include "cauchy-debug.h"

int
main(int argc, char **argv)
{
    CauchyConnectionManager *cm;

    cm = cauchy_connection_manager_new();
    cauchy_connection_manager_run(cm);
    g_object_unref(cm);

    return 0;
}
