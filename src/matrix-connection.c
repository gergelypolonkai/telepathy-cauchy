/*
 * This file is part of telepathy-matrix
 *
 * telepathy-matrix is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation, either
 * version 3 of the * License, or (at your option) any later
 * version.
 *
 * telepathy-matrix is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with telepathy-matrix.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include "matrix-connection.h"

#include "matrix-contact-info.h"

static void _aliasing_iface_init(gpointer, gpointer);

struct _MatrixConnectionPrivate {
    gchar *matrix_id;
    gchar *homeserver;
    gchar *password;
    GHashTable *aliases;
    gboolean dispose_has_run;
    TpSimplePasswordManager *password_manager;
};

enum {
    PROP_0,
    PROP_MATRIX_ID,
    PROP_HOMESERVER,
    PROP_PASSWORD,
    PROP_COUNT
};

static const gchar *interfaces_always_present[] = {
    TP_IFACE_CONNECTION_INTERFACE_ALIASING,
    TP_IFACE_CONNECTION_INTERFACE_CONTACT_INFO,
    /* TODO:
    MATRIX_IFACE_CONNECTION_INTERFACE_RENAMING,
    */
    TP_IFACE_CONNECTION_INTERFACE_REQUESTS,
    TP_IFACE_CONNECTION_INTERFACE_CONTACTS,
    NULL
};

G_DEFINE_TYPE_WITH_CODE(
        MatrixConnection, matrix_connection, TP_TYPE_BASE_CONNECTION,
        G_IMPLEMENT_INTERFACE(
            TP_TYPE_SVC_CONNECTION_INTERFACE_ALIASING,
            _aliasing_iface_init);
        G_IMPLEMENT_INTERFACE(
            TP_TYPE_SVC_CONNECTION_INTERFACE_CONTACT_INFO,
            matrix_contact_info_iface_init);
        /* TODO:
        G_IMPLEMENT_INTERFACE(
            MATRIX_TYPE_SVC_CONNECTION_INTERFACE_RENAMING,
            _renaming_interface_init);
        */
        G_IMPLEMENT_INTERFACE(
            TP_TYPE_SVC_CONNECTION_INTERFACE_CONTACTS,
            tp_contacts_mixin_iface_init);
    );

static void
matrix_connection_set_property(GObject *obj,
                               guint prop_id,
                               const GValue *value,
                               GParamSpec *pspec)
{
    MatrixConnection *connection = MATRIX_CONNECTION(obj);
    MatrixConnectionPrivate *priv = connection->priv;

    switch (prop_id) {
        case PROP_MATRIX_ID:
            g_free(priv->matrix_id);
            priv->matrix_id = g_value_dup_string(value);

            break;

        case PROP_HOMESERVER:
            g_free(priv->homeserver);
            priv->homeserver = g_value_dup_string(value);

            break;

        case PROP_PASSWORD:
            g_free(priv->password);
            priv->password = g_value_dup_string(value);

            break;

        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(obj, prop_id, pspec);

            break;
    }
}

static void
matrix_connection_get_property(GObject *obj,
                               guint prop_id,
                               GValue *value,
                               GParamSpec *pspec)
{
    MatrixConnection *connection = MATRIX_CONNECTION(obj);
    MatrixConnectionPrivate *priv = connection->priv;

    switch (prop_id) {
        case PROP_MATRIX_ID:
            g_value_set_string(value, priv->matrix_id);

            break;

        case PROP_HOMESERVER:
            g_value_set_string(value, priv->homeserver);

            break;

        case PROP_PASSWORD:
            g_value_set_string(value, priv->password);

            break;

        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(obj, prop_id, pspec);

            break;
    }
}

static void
matrix_connection_get_alias_flags(TpSvcConnectionInterfaceAliasing *iface,
                                  DBusGMethodInvocation *context)
{
    tp_svc_connection_interface_aliasing_return_from_get_alias_flags(context, 0);
}

static const gchar *
gimme_an_alias(MatrixConnection *connection,
               TpHandleRepoIface *repo,
               TpHandle handle)
{
    const gchar *alias = g_hash_table_lookup(connection->priv->aliases,
                                             GUINT_TO_POINTER(handle));

    if (alias != NULL) {
        return alias;
    } else {
        return tp_handle_inspect(repo, handle);
    }
}

static void
matrix_connection_get_aliases(TpSvcConnectionInterfaceAliasing *iface,
                              const GArray *handles,
                              DBusGMethodInvocation *context)
{
    MatrixConnection *self = MATRIX_CONNECTION(iface);
    TpHandleRepoIface *repo = tp_base_connection_get_handles(
            TP_BASE_CONNECTION(iface),
            TP_HANDLE_TYPE_CONTACT);
    GError *err = NULL;
    GHashTable *aliases;

    if (!tp_handles_are_valid(repo, handles, FALSE, &err)) {
        dbus_g_method_return_error(context, err);
        g_error_free(err);

        return;
    }

    aliases = g_hash_table_new(NULL, NULL);

    for (guint i = 0; i < handles->len; i++) {
        TpHandle handle = g_array_index(handles, TpHandle, i);

        g_hash_table_insert(aliases,
                            GUINT_TO_POINTER(handle),
                            (gpointer)gimme_an_alias(self, repo, handle));
    }

    tp_svc_connection_interface_aliasing_return_from_get_aliases(context, aliases);
    g_hash_table_unref(aliases);
}

static void
matrix_connection_request_aliases(TpSvcConnectionInterfaceAliasing *iface,
                                  const GArray *handles,
                                  DBusGMethodInvocation *context)
{
    MatrixConnection *connection = MATRIX_CONNECTION(iface);
    TpHandleRepoIface *repo = tp_base_connection_get_handles(
            TP_BASE_CONNECTION(iface), TP_HANDLE_TYPE_CONTACT);
    GError *err = NULL;
    const gchar **aliases;

    if (!tp_handles_are_valid(repo, handles, FALSE, &err)) {
        dbus_g_method_return_error(context, err);
        g_error_free(err);

        return;
    }

    aliases = g_new0(const gchar *, handles->len + 1);

    for (guint i = 0; i < handles->len; i++) {
        TpHandle handle = g_array_index(handles, TpHandle, i);

        aliases[i] = gimme_an_alias(connection, repo, handle);
    }

    tp_svc_connection_interface_aliasing_return_from_request_aliases(context, aliases);
    g_free(aliases);
}

static void
_aliasing_iface_init(gpointer g_iface, gpointer iface_data)
{
    TpSvcConnectionInterfaceAliasingClass *klass = (TpSvcConnectionInterfaceAliasingClass *)g_iface;

#define IMPLEMENT(x) tp_svc_connection_interface_aliasing_implement_##x(klass, matrix_connection_##x)
    IMPLEMENT(get_alias_flags);
    IMPLEMENT(get_aliases);
    IMPLEMENT(request_aliases);
#undef IMPLEMENT
}

static void
matrix_connection_finalize(GObject *gobject)
{
    g_signal_handlers_destroy(gobject);
    G_OBJECT_CLASS(matrix_connection_parent_class)->finalize(gobject);
}

static void
_aliasing_fill_contact_attributes(GObject *obj,
                                  const GArray *contacts,
                                  GHashTable *attributes_hash)
{
    MatrixConnection *connection = MATRIX_CONNECTION(obj);
    TpHandleRepoIface *repo = tp_base_connection_get_handles(
            TP_BASE_CONNECTION(connection),
            TP_HANDLE_TYPE_CONTACT);

    for (guint i = 0; i < contacts->len; i++) {
        TpHandle handle = g_array_index(contacts, TpHandle, i);
        const gchar *alias = gimme_an_alias(connection, repo, handle);

        g_assert(alias != NULL);

        tp_contacts_mixin_set_contact_attribute(
                attributes_hash,
                handle,
                TP_IFACE_CONNECTION_INTERFACE_ALIASING"/alias",
                tp_g_value_slice_new_string(alias));
    }
}

static void
matrix_connection_constructed(GObject *obj)
{
    MatrixConnection *connection = MATRIX_CONNECTION(obj);

    matrix_contact_info_init(connection);
    tp_contacts_mixin_add_contact_attributes_iface(
            obj,
            TP_IFACE_CONNECTION_INTERFACE_ALIASING,
            _aliasing_fill_contact_attributes);
}

static void
matrix_connection_dispose(GObject *obj)
{
    MatrixConnection *connection = MATRIX_CONNECTION(obj);
    MatrixConnectionPrivate *priv = connection->priv;

    if (priv->dispose_has_run) {
        return;
    }

    priv->dispose_has_run = TRUE;

    tp_clear_pointer(&priv->aliases, g_hash_table_unref);

    if (G_OBJECT_CLASS(matrix_connection_parent_class)->dispose) {
        G_OBJECT_CLASS(matrix_connection_parent_class)->dispose(obj);
    }
}

static void
_iface_create_handle_repos(TpBaseConnection *connection,
                           TpHandleRepoIface **repos)
{
    for (int i = 0; i < NUM_TP_HANDLE_TYPES; i++) {
        repos[i] = NULL;
    }

//    TODO matrix_handle_repos_init(repos);
}

static gchar *
_iface_get_unique_connection_name(TpBaseConnection *base)
{
    MatrixConnection *connection = MATRIX_CONNECTION(base);
    MatrixConnectionPrivate *priv = connection->priv;

    return g_strdup_printf(
            "@%s:%s%p",
            priv->matrix_id, priv->homeserver, connection);
}

static GPtrArray *
_iface_create_channel_managers(TpBaseConnection *base)
{
    MatrixConnection *connection = MATRIX_CONNECTION(base);
    MatrixConnectionPrivate *priv = connection->priv;
    GPtrArray *managers = g_ptr_array_sized_new(1);
    //GObject *manager;

    /* TODO:
    manager = g_object_new(MATRIX_TYPE_IM_MANAGER,
                           "connection", connection,
                           NULL);
    g_ptr_array_add(managers, manager);

    manager = g_object_new(MATRIX_TYPE_IM_MUC_MANAGER,
                           "connection", connection,
                           NULL);
    */

    priv->password_manager = tp_simple_password_manager_new(base);
    g_ptr_array_add(managers, priv->password_manager);

    /* TODO:
    manager = g_object_new(MATRIX_TYPE_ROOMLIST_MANAGER,
                           "connection", connection,
                           NULL);
    g_ptr_array_add(managers, manager);

    priv->tls_manager = g_object_new(IDLE_TYPE_SERVER_TLS_MANAGER,
                                     "connection", connection,
                                     NULL);
    g_ptr_array_add(managers, manager);
    */

    return managers;
}

static void
_iface_disconnected(TpBaseConnection *base)
{}

static void
matrix_connection_class_init(MatrixConnectionClass *klass)
{
    GObjectClass *gobject_class = G_OBJECT_CLASS(klass);
    TpBaseConnectionClass *parent_class = TP_BASE_CONNECTION_CLASS(klass);
    GParamSpec *param_spec;

    g_type_class_add_private(klass, sizeof(MatrixConnectionPrivate));

    gobject_class->constructed = matrix_connection_constructed;
    gobject_class->set_property = matrix_connection_set_property;
    gobject_class->get_property = matrix_connection_get_property;
    gobject_class->dispose = matrix_connection_dispose;
    gobject_class->finalize = matrix_connection_finalize;

    parent_class->create_handle_repos = _iface_create_handle_repos;
    parent_class->get_unique_connection_name = _iface_get_unique_connection_name;
    parent_class->create_channel_factories = NULL;
    parent_class->create_channel_managers = _iface_create_channel_managers;
    parent_class->connecting = NULL;
    parent_class->connected = NULL;
    parent_class->disconnected = _iface_disconnected;
    /* TODO:
    parent_class->shut_down = _iface_shut_down;
    parent_class->start_connecting = _iface_start_connecting;
    parent_class->get_interfaces_always_present = get_interfaces_always_present;
    */

    param_spec = g_param_spec_string(
            "matrix-id",
            "Matrix ID",
            "Your registered Matrix ID",
            NULL,
            G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS);
    g_object_class_install_property(gobject_class, PROP_MATRIX_ID, param_spec);

    param_spec = g_param_spec_string(
            "homeserver",
            "Homeserver",
            "The home server to connect to",
            NULL,
            G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS);
    g_object_class_install_property(gobject_class, PROP_HOMESERVER, param_spec);

    param_spec = g_param_spec_string(
            "password",
            "Password",
            "Password to authenticate to the server with",
            NULL,
            G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS);
    g_object_class_install_property(gobject_class, PROP_PASSWORD, param_spec);

    tp_contacts_mixin_class_init(gobject_class, G_STRUCT_OFFSET(MatrixConnectionClass, contacts));
    matrix_contact_info_class_init(klass);
}

static void
matrix_connection_init(MatrixConnection *connection)
{
    MatrixConnectionPrivate *priv = G_TYPE_INSTANCE_GET_PRIVATE(
            connection,
            MATRIX_TYPE_CONNECTION, MatrixConnectionPrivate);

    connection->priv = priv;
    priv->aliases = g_hash_table_new_full(NULL, NULL, NULL, g_free);

    tp_contacts_mixin_init(
            G_OBJECT(connection),
            G_STRUCT_OFFSET(MatrixConnection, contacts));
    tp_base_connection_register_with_contacts_mixin(
            (TpBaseConnection *)connection);
}

const gchar * const *
matrix_connection_get_implemented_interfaces(void)
{
    /* We don’t have any conditionally implemented interfaces */

    return interfaces_always_present;
}
