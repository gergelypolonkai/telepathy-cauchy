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

namespace TelepathyGLib {
    [CCode (cheader_filename = "telepathy-glib/telepathy-glib.h")]
    public abstract class BaseProtocol : GLib.Object {
        [CCode (has_construct_function = false)]
        public BaseProtocol();

        public string name { get; construct; }
    }

    [CCode (cheader_filename = "telepathy-glib/telepathy-glib.h")]
    public abstract class BaseConnectionManager : GLib.Object {
        public class string cm_dbus_name;

        [CCode (has_construct_function = false)]
        public BaseConnectionManager();

        public void
        add_protocol(BaseProtocol protocol);
    }
}