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

#include "cauchy-im-manager.h"

typedef struct _CauchyIMManagerPrivate {
    /* TODO: You must add something here, or GLib will produce warnings! */
} CauchyIMManagerPrivate;

G_DEFINE_TYPE_WITH_PRIVATE(CauchyIMManager, cauchy_im_manager, G_TYPE_OBJECT);

static void
cauchy_im_manager_finalize(GObject *gobject)
{
    g_signal_handlers_destroy(gobject);
    G_OBJECT_CLASS(cauchy_im_manager_parent_class)->finalize(gobject);
}

static void
cauchy_im_manager_class_init(CauchyIMManagerClass *klass)
{
    GObjectClass *gobject_class = G_OBJECT_CLASS(klass);

    gobject_class->finalize = cauchy_im_manager_finalize;
}

static void
cauchy_im_manager_init(CauchyIMManager *im_manager)
{
}
