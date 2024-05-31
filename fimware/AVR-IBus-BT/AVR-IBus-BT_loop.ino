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

void loop() {
  if (Serial.available()) {
    switch (Serial.read()) {
      case 'b':
        Serial.println(F("CMD:stop"));
        a2dp_sink.stop();
        break;
      case 'n':
        Serial.println(F("CMD:next"));
        a2dp_sink.next();
        break;
      case 'p':
        Serial.println(F("CMD:prev"));
        a2dp_sink.previous();
        break;
      case 'r':
        Serial.println(F("CMD:frwd"));
        a2dp_sink.rewind();
        break;
      case 'f':
        Serial.println(F("CMD:ffwd"));
        a2dp_sink.fast_forward();
        break;
      case 's':
        Serial.println(F("CMD:pause"));
        a2dp_sink.pause();
        break;
      case 'm':
        Serial.println(F("CMD:play"));
        a2dp_sink.play();
        break;
      case 'q':
        Serial.printf("CMD:state");
        Serial.printf("\taudio state: %s", a2dp_sink.to_str(a2dp_sink.get_audio_state()));
        Serial.printf("\tbt state: %s\r", a2dp_sink.to_str(a2dp_sink.get_connection_state()));
        //Serial.printf("Volume: %s\r", a2dp_sink.get_volume());
        break;
      case 'x':
        settings_reset();
        break;
      case 'c':
        BTMac();
        break;
    }
  }

  BTSerialLoop();
}
