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

#ifndef __CAUCHY_IM_MANAGER_H__
#define __CAUCHY_IM_MANAGER_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define CAUCHY_TYPE_IM_MANAGER         (cauchy_im_manager_get_type())
#define CAUCHY_IM_MANAGER(o)           (G_TYPE_CHECK_INSTANCE_CAST((o), CAUCHY_TYPE_IM_MANAGER, CauchyIMManager))
#define CAUCHY_IM_MANAGER_CLASS(k)     (G_TYPE_CHECK_CLASS_CAST((k), CAUCHY_TYPE_IM_MANAGER, CauchyIMManagerClass))
#define CAUCHY_IS_IM_MANAGER(o)        (G_TYPE_CHECK_INSTANCE_TYPE((o), CAUCHY_TYPE_IM_MANAGER))
#define CAUCHY_IS_IM_MANAGER_CLASS(k)  (G_TYPE_CHECK_CLASS_TYPE((k), CAUCHY_TYPE_IM_MANAGER))
#define CAUCHY_IM_MANAGER_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS((o), CAUCHY_TYPE_IM_MANAGER, CauchyIMManagerClass))

typedef struct _CauchyIMManager      CauchyIMManager;
typedef struct _CauchyIMManagerClass CauchyIMManagerClass;

struct _CauchyIMManager {
    /* Parent instance structure */
    GObject parent_instance;

    /* Instance members */
};

struct _CauchyIMManagerClass {
    GObjectClass parent_class;
};

GType cauchy_im_manager_get_type(void) G_GNUC_CONST;

G_END_DECLS

#endif /* __CAUCHY_IM_MANAGER_H__ */
