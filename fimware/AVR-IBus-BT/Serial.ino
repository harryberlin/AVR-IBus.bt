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

const int SERIAL_READ_BUFFER_SIZE = 64;
byte serial_read_buffer[SERIAL_READ_BUFFER_SIZE];
byte serial1_read_buffer[SERIAL_READ_BUFFER_SIZE];

void SerialLoop() {
  if (SerialRead()) SerialHandle((char *) serial_read_buffer);
  if (Serial1Read()) SerialHandle((char *) serial1_read_buffer);

  /*
  if (!(millis() % 2000)) {
    Serial1.println("ESP32");
  }
  */
}

bool SerialRead() {
  static byte index;

  if (Serial.available()) {
    byte c = Serial.read();
    //debug_println("BT receive");
    if ((c == '\n' || c == '\r' || c == '\t') && index > 0) {       // wenn LF eingelesen und String länger als 0 ist
      serial_read_buffer[index] = '\0';                             // String terminieren
      index = 0;
      return true;                                              // melden dass String fertig eingelesen wurde
    } else if (c >= 32 && index < SERIAL_READ_BUFFER_SIZE - 1) {      // solange noch Platz im Puffer ist
      serial_read_buffer[index++] = c;                              // Zeichen abspeichern und Index inkrementieren
    }
  }

  return false;                                                 // noch nicht fertig
}

bool Serial1Read() {
  static byte index;

  if (Serial1.available()) {
    byte c = Serial1.read();
    //debug_println("BT receive");
    if ((c == '\n' || c == '\r' || c == '\t') && index > 0) {       // wenn LF eingelesen und String länger als 0 ist
      serial1_read_buffer[index] = '\0';                             // String terminieren
      index = 0;
      return true;                                              // melden dass String fertig eingelesen wurde
    } else if (c >= 32 && index < SERIAL_READ_BUFFER_SIZE - 1) {      // solange noch Platz im Puffer ist
      serial1_read_buffer[index++] = c;                              // Zeichen abspeichern und Index inkrementieren
    }
  }

  return false;                                                 // noch nicht fertig
}

void SerialHandle(String receivedString) {

  switch (receivedString[0]) {
    case 'a':
      switch (receivedString[1]) {
        case 's': //ab
          Serial.println(F("CMD:stop"));
          a2dp_sink.stop();
          break;
        case 'n': //an
          Serial.println(F("CMD:next"));
          a2dp_sink.next();
          break;
        case 'p': //ap
          Serial.println(F("CMD:prev"));
          a2dp_sink.previous();
          break;
        case 'r': //ar
          Serial.println(F("CMD:frwd"));
          a2dp_sink.rewind();
          break;
        case 'f': //af
          Serial.println(F("CMD:ffwd"));
          a2dp_sink.fast_forward();
          break;
        case 'h': //ah
          Serial.println(F("CMD:pause"));
          a2dp_sink.pause();
          break;
        case 'm': //am
          Serial.println(F("CMD:play"));
          a2dp_sink.play();
          break;
      }
    case 'c':
      switch (receivedString[1]) {
        case 's': //cs
          Serial.printf("CMD:state");
          Serial.printf("\taudio state: %s", a2dp_sink.to_str(a2dp_sink.get_audio_state()));
          Serial.printf("\tbt state: %s\r", a2dp_sink.to_str(a2dp_sink.get_connection_state()));
          //Serial.printf("Volume: %s\r", a2dp_sink.get_volume());
          break;
        case 'm': //cm
          BTMac();
          break;
      }
    case 'x':
      settings_reset();
      break;
    default:
      Serial.printf("ESP32:UNKNOWN:%s", receivedString);
  }
  //Serial1.println(receivedString);
}
