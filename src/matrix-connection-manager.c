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
 * License along with telepathy-matrix. If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include "matrix-connection-manager.h"
#include "matrix-protocol.h"
#include "matrix-debug.h"

G_DEFINE_TYPE(MatrixConnectionManager, matrix_connection_manager, TP_TYPE_BASE_CONNECTION_MANAGER);

static void
matrix_connection_manager_finalize(GObject *gobject)
{
    matrix_debug_free();

    G_OBJECT_CLASS(matrix_connection_manager_parent_class)->finalize(gobject);
}

static void
matrix_connection_manager_constructed(GObject *gobject)
{
    TpBaseConnectionManager *base = (TpBaseConnectionManager *)gobject;
    TpBaseProtocol *p;
    void (*constructed)(GObject *) = ((GObjectClass *)matrix_connection_manager_parent_class)->constructed;

    if (constructed != NULL) {
        constructed(gobject);
    }

    p = matrix_protocol_new();
    tp_base_connection_manager_add_protocol(base, p);
    g_object_unref(p);
}

static void
matrix_connection_manager_class_init(MatrixConnectionManagerClass *klass)
{
    GObjectClass *gobject_class = G_OBJECT_CLASS(klass);
    TpBaseConnectionManagerClass *parent_class = TP_BASE_CONNECTION_MANAGER_CLASS(klass);

    parent_class->cm_dbus_name = "matrix";

    gobject_class->finalize = matrix_connection_manager_finalize;
    gobject_class->constructed = matrix_connection_manager_constructed;
}

static void
matrix_connection_manager_init(MatrixConnectionManager *connection_manager)
{
}
