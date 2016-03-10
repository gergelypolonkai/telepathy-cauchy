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

#ifndef __CAUCHY_PROTOCOL_H__
#define __CAUCHY_PROTOCOL_H__

#include <telepathy-glib/telepathy-glib.h>

G_BEGIN_DECLS

#define CAUCHY_TYPE_PROTOCOL         (cauchy_protocol_get_type())
#define CAUCHY_PROTOCOL(o)           (G_TYPE_CHECK_INSTANCE_CAST((o), CAUCHY_TYPE_PROTOCOL, CauchyProtocol))
#define CAUCHY_PROTOCOL_CLASS(k)     (G_TYPE_CHECK_CLASS_CAST((k), CAUCHY_TYPE_PROTOCOL, CauchyProtocolClass))
#define CAUCHY_IS_PROTOCOL(o)        (G_TYPE_CHECK_INSTANCE_TYPE((o), CAUCHY_TYPE_PROTOCOL))
#define CAUCHY_IS_PROTOCOL_CLASS(k)  (G_TYPE_CHECK_CLASS_TYPE((k), CAUCHY_TYPE_PROTOCOL))
#define CAUCHY_PROTOCOL_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS((o), CAUCHY_TYPE_PROTOCOL, CauchyProtocolClass))

typedef struct _CauchyProtocol      CauchyProtocol;
typedef struct _CauchyProtocolClass CauchyProtocolClass;

struct _CauchyProtocol {
    /* Parent instance structure */
    TpBaseProtocol parent_instance;

    /* Instance members */
};

struct _CauchyProtocolClass {
    TpBaseProtocolClass parent_class;
};

GType cauchy_protocol_get_type(void) G_GNUC_CONST;

TpBaseProtocol *cauchy_protocol_new(void);

G_END_DECLS

#endif /* __CAUCHY_PROTOCOL_H__ */
