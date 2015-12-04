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

#ifndef __MATRIX_CONNECTION_MANAGER_H__
#define __MATRIX_CONNECTION_MANAGER_H__

#include <glib-object.h>
#include <telepathy-glib/telepathy-glib.h>

G_BEGIN_DECLS

/* TYPE MACROS */

#define MATRIX_TYPE_CONNECTION_MANAGER         (matrix_connection_manager_get_type())
#define MATRIX_CONNECTION_MANAGER(o)           (G_TYPE_CHECK_INSTANCE_CAST((o), MATRIX_TYPE_CONNECTION_MANAGER, MatrixConnectionManager))
#define MATRIX_CONNECTION_MANAGER_CLASS(k)     (G_TYPE_CHECK_CLASS_CAST((k), MATRIX_TYPE_CONNECTION_MANAGER, MatrixConnectionManagerClass))
#define MATRIX_IS_CONNECTION_MANAGER(o)        (G_TYPE_CHECK_INSTANCE_TYPE((o), MATRIX_TYPE_CONNECTION_MANAGER))
#define MATRIX_IS_CONNECTION_MANAGER_CLASS(k)  (G_TYPE_CHECK_CLASS_TYPE((k), MATRIX_TYPE_CONNECTION_MANAGER))
#define MATRIX_CONNECTION_MANAGER_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS((o), MATRIX_TYPE_CONNECTION_MANAGER, MatrixConnectionManagerClass))

typedef struct _MatrixConnectionManager MatrixConnectionManager;
typedef struct _MatrixConnectionManagerClass MatrixConnectionManagerClass;

struct _MatrixConnectionManagerClass {
    TpBaseConnectionManagerClass parent_class;
};

struct _MatrixConnectionManager {
    /* Parent instance structure */
    TpBaseConnection parent;

    /* Instance members */
};

GType matrix_connection_manager_get_type(void) G_GNUC_CONST;

G_END_DECLS

#endif /* __MATRIX_CONNECTION_MANAGER_H__ */
