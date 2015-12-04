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

#ifndef __MATRIX_PROTOCOL_H__
#define __MATRIX_PROTOCOL_H__

#include <telepathy-glib/telepathy-glib.h>

G_BEGIN_DECLS

#define MATRIX_TYPE_PROTOCOL         (matrix_protocol_get_type())
#define MATRIX_PROTOCOL(o)           (G_TYPE_CHECK_INSTANCE_CAST((o), MATRIX_TYPE_PROTOCOL, MatrixProtocol))
#define MATRIX_PROTOCOL_CLASS(k)     (G_TYPE_CHECK_CLASS_CAST((k), MATRIX_TYPE_PROTOCOL, MatrixProtocolClass))
#define MATRIX_IS_PROTOCOL(o)        (G_TYPE_CHECK_INSTANCE_TYPE((o), MATRIX_TYPE_PROTOCOL))
#define MATRIX_IS_PROTOCOL_CLASS(k)  (G_TYPE_CHECK_CLASS_TYPE((k), MATRIX_TYPE_PROTOCOL))
#define MATRIX_PROTOCOL_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS((o), MATRIX_TYPE_PROTOCOL, MatrixProtocolClass))

typedef struct _MatrixProtocol      MatrixProtocol;
typedef struct _MatrixProtocolClass MatrixProtocolClass;

struct _MatrixProtocol {
    /* Parent instance structure */
    TpBaseProtocol parent_instance;

    /* Instance members */
};

struct _MatrixProtocolClass {
    TpBaseProtocolClass parent_class;
};

GType matrix_protocol_get_type(void) G_GNUC_CONST;

TpBaseProtocol *matrix_protocol_new(void);

G_END_DECLS

#endif /* __MATRIX_PROTOCOL_H__ */
