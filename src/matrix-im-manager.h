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

#ifndef __MATRIX_IM_MANAGER_H__
#define __MATRIX_IM_MANAGER_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define MATRIX_TYPE_IM_MANAGER         (matrix_im_manager_get_type())
#define MATRIX_IM_MANAGER(o)           (G_TYPE_CHECK_INSTANCE_CAST((o), MATRIX_TYPE_IM_MANAGER, MatrixIMManager))
#define MATRIX_IM_MANAGER_CLASS(k)     (G_TYPE_CHECK_CLASS_CAST((k), MATRIX_TYPE_IM_MANAGER, MatrixIMManagerClass))
#define MATRIX_IS_IM_MANAGER(o)        (G_TYPE_CHECK_INSTANCE_TYPE((o), MATRIX_TYPE_IM_MANAGER))
#define MATRIX_IS_IM_MANAGER_CLASS(k)  (G_TYPE_CHECK_CLASS_TYPE((k), MATRIX_TYPE_IM_MANAGER))
#define MATRIX_IM_MANAGER_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS((o), MATRIX_TYPE_IM_MANAGER, MatrixIMManagerClass))

typedef struct _MatrixIMManager      MatrixIMManager;
typedef struct _MatrixIMManagerClass MatrixIMManagerClass;

struct _MatrixIMManager {
    /* Parent instance structure */
    GObject parent_instance;

    /* Instance members */
};

struct _MatrixIMManagerClass {
    GObjectClass parent_class;
};

GType matrix_im_manager_get_type(void) G_GNUC_CONST;

G_END_DECLS

#endif /* __MATRIX_IM_MANAGER_H__ */
