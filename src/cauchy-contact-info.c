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

#include "cauchy-contact-info.h"

#define CAUCHY_DEBUG_FLAG CAUCHY_DEBUG_CONNECTION
#include "cauchy-debug.h"

typedef enum _ContactPresence {
    CONTACT_PRESENCE_UNKNOWN,
    CONTACT_PRESENCE_AVAILABLE,
    CONTACT_PRESENCE_AWAY,
    CONTACT_PRESENCE_DND,
    CONTACT_PRESENCE_ERROR
} ContactPresence;

typedef struct _ContactInfoRequest {
    guint handle;
    const gchar *id;
    ContactPresence presence;
    GPtrArray *contact_info;
    DBusGMethodInvocation *context;
} ContactInfoRequest;

static void
cauchy_contact_info_properties_getter(GObject *gobject,
                                      GQuark interface,
                                      GQuark name,
                                      GValue *value,
                                      gpointer getter_data)
{
    GQuark q_supported_fields = g_quark_from_static_string("SupportedFields");

    if (name == q_supported_fields) {
        GPtrArray *fields = dbus_g_type_specialized_construct(
                TP_ARRAY_TYPE_FIELD_SPECS);

        g_value_set_boxed(value, fields);
        g_boxed_free(TP_ARRAY_TYPE_FIELD_SPECS, fields);
    } else {
        g_value_set_uint(value, 0);
    }
}

void
cauchy_contact_info_class_init(CauchyConnectionClass *klass)
{
    GObjectClass *gobject_class = G_OBJECT_CLASS(klass);

    static TpDBusPropertiesMixinPropImpl props[] = {
        {"ContactInfoFlags", NULL, NULL},
        {"SupportedFields", NULL, NULL},
        {NULL}
    };

    tp_dbus_properties_mixin_implement_interface(
            gobject_class,
            TP_IFACE_QUARK_CONNECTION_INTERFACE_CONTACT_INFO,
            cauchy_contact_info_properties_getter,
            NULL,
            props);
}

static void
cauchy_contact_info_fill_contact_attributes(GObject *gobject,
                                            const GArray *contacts,
                                            GHashTable *attributes_hash)
{
    /* We don’t cache contact info yet. */
}

void
cauchy_contact_info_init(CauchyConnection *connection)
{
    connection->contact_info_requests = g_queue_new();

    /* TODO: add handlers here */

    tp_contacts_mixin_add_contact_attributes_iface(
            G_OBJECT(connection),
            TP_IFACE_CONNECTION_INTERFACE_CONTACT_INFO,
            cauchy_contact_info_fill_contact_attributes);
}

static void
_send_request_contact_info(CauchyConnection *connection,
                           ContactInfoRequest *request)
{
    // TODO: implement actual contact info querying
}

static void
_queue_request_contact_info(CauchyConnection *connection,
                            guint handle,
                            const gchar *id,
                            DBusGMethodInvocation *context)
{
    ContactInfoRequest *request;

    request = g_slice_new0(ContactInfoRequest);
    request->handle = handle;
    request->id = id;
    request->presence = CONTACT_PRESENCE_UNKNOWN;
    request->contact_info = NULL;
    request->context = context;

    if (g_queue_is_empty(connection->contact_info_requests)) {
        _send_request_contact_info(connection, request);
    }

    g_queue_push_tail(connection->contact_info_requests, request);
}

static void
cauchy_connection_request_contact_info(
        TpSvcConnectionInterfaceContactInfo *iface,
        guint contact,
        DBusGMethodInvocation *context)
{
    CauchyConnection *connection = CAUCHY_CONNECTION(iface);
    TpBaseConnection *base = TP_BASE_CONNECTION(connection);
    TpHandleRepoIface *contact_handles = tp_base_connection_get_handles(
            base,
            TP_HANDLE_TYPE_CONTACT);
    const gchar *id;
    GError *err = NULL;

    TP_BASE_CONNECTION_ERROR_IF_NOT_CONNECTED(base, context);

    if (!tp_handle_is_valid(contact_handles, contact, &err)) {
        dbus_g_method_return_error(context, err);
        g_error_free(err);

        return;
    }

    id = tp_handle_inspect(contact_handles, contact);

    CAUCHY_DEBUG("Queued contact info request for handle: %u (%s)",
                 contact, id);

    _queue_request_contact_info(connection, contact, id, context);
}

void
cauchy_contact_info_iface_init(gpointer g_iface, gpointer iface_data)
{
    TpSvcConnectionInterfaceContactInfoClass *klass = (TpSvcConnectionInterfaceContactInfoClass *)g_iface;

#define IMPLEMENT(x) tp_svc_connection_interface_contact_info_implement_##x (klass, cauchy_connection_##x)
    IMPLEMENT(request_contact_info);
#undef IMPLEMENT
}
