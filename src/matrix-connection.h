/*
 * This file is part of telepathy-matrix
 *
 * telepathy-matrix is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation, either
 * version 3 of * the License, or (at your option) any later version.
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

#ifndef __MATRIX_CONNECTION_H__
#define __MATRIX_CONNECTION_H__

#include <glib-object.h>
#include <telepathy-glib/telepathy-glib.h>

G_BEGIN_DECLS

#define MATRIX_TYPE_CONNECTION         (matrix_connection_get_type())
#define MATRIX_CONNECTION(o)           (G_TYPE_CHECK_INSTANCE_CAST((o), MATRIX_TYPE_CONNECTION, MatrixConnection))
#define MATRIX_CONNECTION_CLASS(k)     (G_TYPE_CHECK_CLASS_CAST((k), MATRIX_TYPE_CONNECTION, MatrixConnectionClass))
#define MATRIX_IS_CONNECTION(o)        (G_TYPE_CHECK_INSTANCE_TYPE((o), MATRIX_TYPE_CONNECTION))
#define MATRIX_IS_CONNECTION_CLASS(k)  (G_TYPE_CHECK_CLASS_TYPE((k), MATRIX_TYPE_CONNECTION))
#define MATRIX_CONNECTION_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS((o), MATRIX_TYPE_CONNECTION, MatrixConnectionClass))

typedef struct _MatrixConnection        MatrixConnection;
typedef struct _MatrixConnectionClass   MatrixConnectionClass;
typedef struct _MatrixConnectionPrivate MatrixConnectionPrivate;

struct _MatrixConnection {
    /* Parent instance structure */
    TpBaseConnection parent_instance;
    TpContactsMixin contacts;

    /* Instance members */
    MatrixConnectionPrivate *priv;
};

struct _MatrixConnectionClass {
    TpBaseConnectionClass parent_class;
    TpContactsMixinClass contacts;
};

GType matrix_connection_get_type(void) G_GNUC_CONST;

G_END_DECLS

#endif /* __MATRIX_CONNECTION_H__ */
