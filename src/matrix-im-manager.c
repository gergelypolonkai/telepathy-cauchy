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

#include "matrix-im-manager.h"

typedef struct _MatrixIMManagerPrivate {
    /* TODO: You must add something here, or GLib will produce warnings! */
} MatrixIMManagerPrivate;

G_DEFINE_TYPE_WITH_PRIVATE(MatrixIMManager, matrix_im_manager, G_TYPE_OBJECT);

static void
matrix_im_manager_finalize(GObject *gobject)
{
    g_signal_handlers_destroy(gobject);
    G_OBJECT_CLASS(matrix_im_manager_parent_class)->finalize(gobject);
}

static void
matrix_im_manager_class_init(MatrixIMManagerClass *klass)
{
    GObjectClass *gobject_class = G_OBJECT_CLASS(klass);

    gobject_class->finalize = matrix_im_manager_finalize;
}

static void
matrix_im_manager_init(MatrixIMManager *im_manager)
{
}
