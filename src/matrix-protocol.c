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

#include "matrix-protocol.h"
#include "matrix-handles.h"
#include "matrix-connection.h"

#include <dbus/dbus-protocol.h>

#define PROTOCOL_NAME "matrix"

static gboolean filter_account(const TpCMParamSpec *, GValue *, GError **);

static const TpCMParamSpec matrix_params[] = {
    {
        "account",
        DBUS_TYPE_STRING_AS_STRING, G_TYPE_STRING,
        TP_CONN_MGR_PARAM_FLAG_REQUIRED,
        NULL, 0, filter_account
    },
    {
        "homeserver",
        DBUS_TYPE_STRING_AS_STRING, G_TYPE_STRING,
        TP_CONN_MGR_PARAM_FLAG_REQUIRED
    },
    {
        "password",
        DBUS_TYPE_STRING_AS_STRING, G_TYPE_STRING,
        TP_CONN_MGR_PARAM_FLAG_SECRET
    },
    {NULL, NULL, 0, 0, NULL, 0}
};

G_DEFINE_TYPE(MatrixProtocol, matrix_protocol, TP_TYPE_BASE_PROTOCOL);

static gboolean
filter_account(const TpCMParamSpec *paramspec, GValue *value, GError **err)
{
    const gchar *matrixid = g_value_get_string(value);

    g_assert(matrixid);
    g_assert(G_VALUE_HOLDS_STRING(value));

    if (!matrix_id_is_valid(matrixid, TRUE)) {
        g_set_error(err,
                    TP_ERROR, TP_ERROR_INVALID_HANDLE,
                    "Invalid account name '%s'", matrixid);

        return FALSE;
    }

    return TRUE;
}

static const TpCMParamSpec *
get_parameters(TpBaseProtocol *self G_GNUC_UNUSED)
{
    return matrix_params;
}

static TpBaseConnection *
new_connection(TpBaseProtocol *protocol G_GNUC_UNUSED,
               GHashTable *params,
               GError **err G_GNUC_UNUSED)
{
    return g_object_new(MATRIX_TYPE_CONNECTION,
                        "homeserver", tp_asv_get_string(params, "homeserver"),
                        "matrix_id", tp_asv_get_string(params, "account"),
                        "password", tp_asv_get_string(params, "password"),
                        NULL);
}

static gchar *
normalize_contact(TpBaseProtocol *protocol G_GNUC_UNUSED,
                  const gchar *contact,
                  GError **err)
{
    return matrix_normalize_id(contact, err);
}

static gchar *
identify_account(TpBaseProtocol *protocol G_GNUC_UNUSED,
                 GHashTable *asv,
                 GError **err)
{
    gchar *id = matrix_normalize_id(tp_asv_get_string(asv, "account"), err);
    gchar *server;
    gchar *id_at_server;

    if (id == NULL) {
        return NULL;
    }

    server = g_ascii_strdown(tp_asv_get_string(asv, "homeserver"), -1);

    id_at_server = g_strdup_printf("@%s:%s", id, server);
    g_free(server);
    g_free(id);

    return id_at_server;
}

static GPtrArray *
get_interfaces_array(TpBaseProtocol *protocol)
{
    GPtrArray *interfaces;

    interfaces = TP_BASE_PROTOCOL_CLASS(matrix_protocol_parent_class)->get_interfaces_array(protocol);

    return interfaces;
}

static void
matrix_protocol_class_init(MatrixProtocolClass *klass)
{
    TpBaseProtocolClass *base_class = (TpBaseProtocolClass *)klass;

    base_class->get_parameters = get_parameters;
    base_class->new_connection = new_connection;
    base_class->normalize_contact = normalize_contact;
    base_class->identify_account = identify_account;
    base_class->get_interfaces_array = get_interfaces_array;
    /*
    base_class->get_connection_details = get_connection_details;
    base_class->dup_authentication_types = dup_authentication_types;
    */
}

static void
matrix_protocol_init(MatrixProtocol *protocol)
{
}

TpBaseProtocol *
matrix_protocol_new(void)
{
    return g_object_new(MATRIX_TYPE_PROTOCOL,
                        "name", PROTOCOL_NAME,
                        NULL);
}
