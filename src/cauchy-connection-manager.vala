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

using TelepathyGLib;

[DBus (name = "org.freedesktop.Telepathy.ConnectionManager")]
public class Cauchy.ConnectionManager : Object {
    public struct CMParams {
        string name;
        ConnMgrParamFlags flags;
        string signature;
        Variant default_value;
    }

    public unowned string
    get_name()
        throws TelepathyGLib.Error
    {
        return "cauchy";
    }

    public bool
    has_protocol(string protocol)
        throws TelepathyGLib.Error
    {
        return (protocol == "matrix");
    }

    public void
    get_parameters(string protocol,
                   out CMParams[] parameters)
        throws TelepathyGLib.Error
    {
        parameters = {
            };

        parameters += CMParams() {
            name = "account",
            flags = ConnMgrParamFlags.REQUIRED,
            signature = "s",
            default_value = new Variant.maybe(VariantType.STRING, null)
        };
    }

    private void
    on_bus_acquired(DBusConnection conn)
    {
        try {
            conn.register_object(
                    "/org/freedesktop/Telepathy/ConnectionManager/cauchy",
                    this);
        } catch (IOError e) {
            stderr.printf("Could not register service: %s\n", e.message);
        }

        try {
            conn.register_object(
                    "/org/freedesktop/Telepathy/ConnectionManager/cauchy/matrix",
                    new Cauchy.Protocol());
        } catch (IOError e) {
            stderr.printf("Could not register protocol: %s\n", e.message);
        }
    }

    public void
    run()
    {
        Bus.own_name(BusType.SESSION,
                     "org.freedesktop.Telepathy.ConnectionManager.cauchy",
                     BusNameOwnerFlags.NONE,
                     on_bus_acquired,
                     () => {},
                     () => stderr.printf("Could not acquire name.\n"));

        new MainLoop().run();
    }
}
