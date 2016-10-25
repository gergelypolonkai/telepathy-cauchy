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

using TelepathyGLib;

[DBus (name = "org.freedesktop.Telepathy.Protocol")]
public class Cauchy.Protocol : Object {
    public void
    identify_account(HashTable<string, Variant> parameters,
                     out string account_id)
        throws TelepathyGLib.Error
    {
        throw new TelepathyGLib.Error.NOT_IMPLEMENTED(
                "This feature is not implemented");
    }

    public void
    normalize_contact(string contact_id, out string normalized_contact_id)
        throws TelepathyGLib.Error
    {
        throw new TelepathyGLib.Error.NOT_IMPLEMENTED(
                "This feature is meaningless on Matrix");
    }
}
