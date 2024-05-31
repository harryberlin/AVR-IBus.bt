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

void BTSerialLoop() {
  if (SerialBT.available()) {
    Serial.print("BT:");
    Serial.write(SerialBT.read());
  }

}

void BTMac() {
  uint8_t mac_arr[6]; // Byte array to hold the MAC address from getBtAddress()
  BTAddress mac_obj; // Object holding instance of BTAddress with the MAC (for more details see libraries/BluetoothSerial/src/BTAddress.h)
  String mac_str; // String holding the text version of MAC in format AA:BB:CC:DD:EE:FF

  SerialBT.getBtAddress(mac_arr); // Fill in the array
  mac_obj = SerialBT.getBtAddressObject(); // Instantiate the object
  mac_str = SerialBT.getBtAddressString(); // Copy the string

  Serial.print("This device is instantiated with name "); Serial.println(settings_btname_get().c_str());

  Serial.print("The mac address using byte array: ");
  for (int i = 0; i < ESP_BD_ADDR_LEN - 1; i++) {
    Serial.print(mac_arr[i], HEX); Serial.print(":");
  }
  Serial.println(mac_arr[ESP_BD_ADDR_LEN - 1], HEX);

  Serial.print("The mac address using BTAddress object using default method `toString()`: "); Serial.println(mac_obj.toString().c_str());
  Serial.print("The mac address using BTAddress object using method `toString(true)`\n\twhich prints the MAC with capital letters: "); Serial.println(mac_obj.toString(true).c_str()); // This actually what is used inside the getBtAddressString()

  Serial.print("The mac address using string: "); Serial.println(mac_str.c_str());

  SerialBT.println(settings_btname_get());
}
