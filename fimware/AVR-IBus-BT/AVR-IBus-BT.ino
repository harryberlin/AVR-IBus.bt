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

#define DEBUG

#ifdef DEBUG    //Macros are usually in all capital lettersIoIf.println(.
#define debug_print(...)    Serial.print(__VA_ARGS__)     //debug_print is a macro, debug print
#define debug_println(...)  Serial.println(__VA_ARGS__)   //debug_println is a macro, debug print with new line
#define debug_sprintf(...)  Serial.printf(__VA_ARGS__)
#else
#define debug_print(...)     //now defines a blank line
#define debug_println(...)   //now defines a blank line
#define debug_sprintf(...)   //now defines a blank line
#endif

#include "EEPROM.h"
#define EEPROM_SIZE 128

//#define USE_AUDIO_LOGGING true

#include "AudioTools.h"
I2SStream i2s;

//#include "BluetoothA2DPSink.h"
//BluetoothA2DPSink a2dp_sink(i2s);

#include "BluetoothA2DPSinkQueued.h"
BluetoothA2DPSinkQueued a2dp_sink(i2s);

#include "BluetoothSerial.h"
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial BTSerial;
#define RXPIN 19         // GPIO 19 => RX for Serial1
#define TXPIN 18        // GPIO 18 => TX for Serial1


const PROGMEM byte FIRST_SETUP = 0;

// for esp_a2d_connection_state_t see https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/bluetooth/esp_a2dp.html#_CPPv426esp_a2d_connection_state_t
void connection_state_changed(esp_a2d_connection_state_t state, void *ptr) {
  Serial.print(state, HEX);
  Serial.print("::");
  Serial.println(a2dp_sink.to_str(state));
  switch (state) {
    case 0:
      Serial.println("Disconnected");
      break;    
    case 1:
      Serial.println("Connecting");
      break;
    case 2:
      Serial.println("Connected");
      a2dp_sink.pause();
      Serial1.print("aq\r");
      a2dp_sink.set_volume(0xFF);
      break;    
    default:
      Serial.printf("Got unknown Connection status %d\n", state);
  }

}

// for esp_a2d_audio_state_t see https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/bluetooth/esp_a2dp.html#_CPPv421esp_a2d_audio_state_t
void audio_state_changed(esp_a2d_audio_state_t state, void *ptr) {
  Serial.print(state, HEX);
  Serial.print("::");
  Serial.println(a2dp_sink.to_str(state));
}

///TESTTTTTTTT
void avrc_rn_play_pos_callback(uint32_t play_pos) {
  Serial.printf("Play position is %d (%d seconds)\n", play_pos, (int)round(play_pos / 1000.0));
}

void avrc_rn_playstatus_callback(esp_avrc_playback_stat_t playback) {
  Serial.print(playback, HEX);
  Serial.print("::");
  switch (playback) {
    case esp_avrc_playback_stat_t::ESP_AVRC_PLAYBACK_STOPPED:
      Serial.println("Stopped.");
      break;
    case esp_avrc_playback_stat_t::ESP_AVRC_PLAYBACK_PLAYING:
      Serial.println("Playing.");
      break;
    case esp_avrc_playback_stat_t::ESP_AVRC_PLAYBACK_PAUSED:
      Serial.println("Paused.");
      break;
    case esp_avrc_playback_stat_t::ESP_AVRC_PLAYBACK_FWD_SEEK:
      Serial.println("Forward seek.");
      break;
    case esp_avrc_playback_stat_t::ESP_AVRC_PLAYBACK_REV_SEEK:
      Serial.println("Reverse seek.");
      break;
    case esp_avrc_playback_stat_t::ESP_AVRC_PLAYBACK_ERROR:
      Serial.println("Error.");
      break;
    default:
      Serial.printf("Got unknown playback status %d\n", playback);
  }
}

void avrc_rn_track_change_callback(uint8_t *id) {
  Serial.println("Track Change bits:");
  for (uint8_t i = 0; i < 8; i++)
  {
    Serial.printf("\tByte %d : 0x%x \n", i, id[i]);
  }
  //An example of how to project the pointer value directly as a uint8_t
  uint8_t track_change_flag = *id;
  Serial.printf("\tFlag value: %d\n", track_change_flag);
}


///TESTTTTTTTT

void a2dp_init() {
  auto cfg = i2s.defaultConfig();
  cfg.pin_bck = 26;
  cfg.pin_ws = 25;
  cfg.pin_data = 22;
  i2s.begin(cfg);


  a2dp_sink.set_on_connection_state_changed(connection_state_changed);
  a2dp_sink.set_on_audio_state_changed(audio_state_changed);


  a2dp_sink.set_avrc_rn_playstatus_callback(avrc_rn_playstatus_callback);
  //a2dp_sink.set_avrc_rn_play_pos_callback(avrc_rn_play_pos_callback, 5); //Update the playing position every 5 seconds when Playing
  //a2dp_sink.set_avrc_rn_track_change_callback(avrc_rn_track_change_callback);


  a2dp_sink.set_auto_reconnect(true);

  a2dp_sink.start(settings_btname_get().c_str());

}
