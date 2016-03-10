/*
 * This file is part of telepathy-cauchy
 *
 * telepathy-cauchy is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version.
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

#ifndef __CAUCHY_CONTACT_INFO_H__
#define __CAUCHY_CONTACT_INFO_H__

#include <glib.h>
#include <glib-object.h>
#include <telepathy-glib/telepathy-glib.h>

#include "cauchy-connection.h"

G_BEGIN_DECLS

void cauchy_contact_info_class_init(CauchyConnectionClass *klass);
void cauchy_contact_info_iface_init(gpointer g_iface, gpointer iface_data);
void cauchy_contact_info_init(CauchyConnection *connection);

G_END_DECLS

#endif /* __CAUCHY_CONTACT_INFO_H__ */
