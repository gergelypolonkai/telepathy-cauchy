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

#include "matrix-protocol.h"

#define PROTOCOL_NAME "matrix"

G_DEFINE_TYPE(MatrixProtocol, matrix_protocol, TP_TYPE_BASE_PROTOCOL);

static void
matrix_protocol_finalize(GObject *gobject)
{
    g_signal_handlers_destroy(gobject);
    G_OBJECT_CLASS(matrix_protocol_parent_class)->finalize(gobject);
}

static void
matrix_protocol_class_init(MatrixProtocolClass *klass)
{
    GObjectClass *gobject_class = G_OBJECT_CLASS(klass);

    gobject_class->finalize = matrix_protocol_finalize;
}

static void
matrix_protocol_init(MatrixProtocol *protocol)
{
}

TpBaseProtocol *
matrix_protocol_new(void)
{
    return g_object_new(MATRIX_TYPE_PROTOCOL,
                        "name", PROTOCOL_NAME,
                        NULL);
}
