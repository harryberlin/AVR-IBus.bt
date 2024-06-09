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

// for esp_a2d_connection_state_t see https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/bluetooth/esp_a2dp.html#_CPPv426esp_a2d_connection_state_t

#include "esp_gap_bt_api.h"
void connection_state_changed(esp_a2d_connection_state_t state, void *ptr) {
  //Serial.print(state, HEX);
  //Serial.print("::");
  //Serial.println(a2dp_sink.to_str(state));
  switch (state) {
    case 0:
      Serial.print("Disconnected");
      break;
    case 1:
      Serial.print("Connecting");
      break;
    case 2:
      memcpy(bt_mac_address, (*a2dp_sink.get_current_peer_address()), 6);
      printMacAddress();

      a2dp_sink.set_volume(127);

      Serial.print("Connected");
      break;
    default:
      Serial.printf("Got unknown Connection status %d\n", state);
  }
  Serial.printf("::");
  printConnectionState();

}


void printConnectionState() {
  Serial.printf("C%d\r\n", a2dp_sink.get_connection_state() );
  Serial1.printf("C%d\r", a2dp_sink.get_connection_state() );
}

void printMacAddress() {
  Serial1.print("CA:");
  for (int i = 0; i < 5; i++) {
    Serial1.print((bt_mac_address)[i], HEX);
    Serial1.print(":");
    Serial.print((bt_mac_address)[i], HEX);
    Serial.print(":");
  }
  Serial1.println((bt_mac_address)[5], HEX);
  Serial.println((bt_mac_address)[5], HEX);

}
