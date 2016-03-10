/*
 * This file is part of telepathy-cauchy
 *
 * telepathy-cauchy is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation, either
 * version 3 of * the License, or (at your option) any later version.
 *
 * telepathy-cauchy is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with telepathy-cauchy. If not, see
 * <http://www.gnu.org/licenses/>.
 */

#ifndef __CAUCHY_CONNECTION_H__
#define __CAUCHY_CONNECTION_H__

#include <glib-object.h>
#include <telepathy-glib/telepathy-glib.h>

G_BEGIN_DECLS

#define CAUCHY_TYPE_CONNECTION         (cauchy_connection_get_type())
#define CAUCHY_CONNECTION(o)           (G_TYPE_CHECK_INSTANCE_CAST((o), CAUCHY_TYPE_CONNECTION, CauchyConnection))
#define CAUCHY_CONNECTION_CLASS(k)     (G_TYPE_CHECK_CLASS_CAST((k), CAUCHY_TYPE_CONNECTION, CauchyConnectionClass))
#define CAUCHY_IS_CONNECTION(o)        (G_TYPE_CHECK_INSTANCE_TYPE((o), CAUCHY_TYPE_CONNECTION))
#define CAUCHY_IS_CONNECTION_CLASS(k)  (G_TYPE_CHECK_CLASS_TYPE((k), CAUCHY_TYPE_CONNECTION))
#define CAUCHY_CONNECTION_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS((o), CAUCHY_TYPE_CONNECTION, CauchyConnectionClass))

typedef struct _CauchyConnection        CauchyConnection;
typedef struct _CauchyConnectionClass   CauchyConnectionClass;
typedef struct _CauchyConnectionPrivate CauchyConnectionPrivate;

struct _CauchyConnection {
    /* Parent instance structure */
    TpBaseConnection parent_instance;
    TpContactsMixin contacts;
    GQueue *contact_info_requests;

    /* Instance members */
    CauchyConnectionPrivate *priv;
};

struct _CauchyConnectionClass {
    TpBaseConnectionClass parent_class;
    TpContactsMixinClass contacts;
};

GType cauchy_connection_get_type(void) G_GNUC_CONST;

const gchar * const *cauchy_connection_get_implemented_interfaces(void);

G_END_DECLS

#endif /* __CAUCHY_CONNECTION_H__ */
