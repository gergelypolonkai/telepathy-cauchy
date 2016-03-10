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

#ifndef __CAUCHY_DEBUG_H__
#define __CAUCHY_DEBUG_H__

#include <glib.h>

typedef enum {
    CAUCHY_DEBUG_CONNECTION = (1 << 0),
    CAUCHY_DEBUG_DNS = (1 << 1),
    CAUCHY_DEBUG_IM = (1 << 2),
    CAUCHY_DEBUG_MUC = (1 << 3),
    CAUCHY_DEBUG_NETWORK = (1 << 4),
    CAUCHY_DEBUG_PARSER = (1 << 5),
    CAUCHY_DEBUG_TEXT = (1 << 6),
    CAUCHY_DEBUG_ROOMLIST = (1 << 7),
    CAUCHY_DEBUG_TLS = (1 << 8),
} CauchyDebugFlags;

void cauchy_debug_init (void);
void cauchy_debug(CauchyDebugFlags flag, const gchar *format, ...) G_GNUC_PRINTF(2, 3);

void cauchy_debug_free (void);

#endif /* __CAUCHY_DEBUG_H__ */

#ifdef CAUCHY_DEBUG_FLAG
# undef CAUCHY_DEBUG
# define CAUCHY_DEBUG(format, ...) \
    cauchy_debug(CAUCHY_DEBUG_FLAG, "%s: " format, G_STRFUNC, ##__VA_ARGS__)
#endif /* CAUCHY_DEBUG_FLAG */
