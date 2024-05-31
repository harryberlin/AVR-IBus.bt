/*
  Author: Christian Kiesewetter
  Copyright (c) 2024 Christian Kiesewetter.  All right reserved.

  avr-ibus@gmx.net

  Don't share without agreement of the author.

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

void settings_reset() {
  settings_btname_set("AVR-IBus-BT");
  EEPROM.write(FIRST_SETUP, 0x01);
  EEPROM.commit();
  Serial.println("Settings Reset Done");
}

void settings_btname_set(String sentence) {
  EEPROM.writeString(101, sentence);
}

String settings_btname_get() {
  return EEPROM.readString(101);
}
