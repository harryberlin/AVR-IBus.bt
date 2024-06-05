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

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200, SERIAL_8N1, RXPIN, TXPIN); // Rx = 4, Tx = 5 will work for ESP32, S2, S3 and C3
  //AudioLogger::instance().begin(Serial, AudioLogger::Info);

  if (!EEPROM.begin(EEPROM_SIZE)) {
    Serial.println("failed to initialise EEPROM");
  }

  //check setup
  //debug_println(EEPROM.read(FIRST_SETUP), HEX);
  if (EEPROM.read(FIRST_SETUP) != 1) {
    settings_reset();
  }
  //debug_println(EEPROM.read(FIRST_SETUP), HEX);

  a2dp_init();

  BTSerial.begin(settings_btname_get().c_str());

}
