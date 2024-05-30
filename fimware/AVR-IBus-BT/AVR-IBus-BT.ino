/*
  Streaming Music from Bluetooth

  Copyright (C) 2020 Phil Schatzmann
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// ==> Example which shows how to use the built in ESP32 I2S < 3.0.0
//#define USE_AUDIO_LOGGING true

#include "AudioTools.h"
//#include "BluetoothA2DPSink.h"
#include "BluetoothA2DPSinkQueued.h"

//#define LOG_LEVEL AudioLogger::Debug
//#define LOG_STREAM Serial


I2SStream i2s;
//BluetoothA2DPSink a2dp_sink(i2s);
BluetoothA2DPSinkQueued a2dp_sink(i2s);

// for esp_a2d_connection_state_t see https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/bluetooth/esp_a2dp.html#_CPPv426esp_a2d_connection_state_t
void connection_state_changed(esp_a2d_connection_state_t state, void *ptr) {
  Serial.println(a2dp_sink.to_str(state));
}

// for esp_a2d_audio_state_t see https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/bluetooth/esp_a2dp.html#_CPPv421esp_a2d_audio_state_t
void audio_state_changed(esp_a2d_audio_state_t state, void *ptr) {
  Serial.println(a2dp_sink.to_str(state));
}

///TESTTTTTTTT
void avrc_rn_play_pos_callback(uint32_t play_pos) {
  Serial.printf("Play position is %d (%d seconds)\n", play_pos, (int)round(play_pos / 1000.0));
}

void avrc_rn_playstatus_callback(esp_avrc_playback_stat_t playback) {
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

void setup() {
  Serial.begin(115200);
  //AudioLogger::instance().begin(Serial, AudioLogger::Info);

  auto cfg = i2s.defaultConfig();
  cfg.pin_bck = 26;
  cfg.pin_ws = 25;
  cfg.pin_data = 22;
  i2s.begin(cfg);


  a2dp_sink.set_on_connection_state_changed(connection_state_changed);
  a2dp_sink.set_on_audio_state_changed(audio_state_changed);
  a2dp_sink.set_auto_reconnect(true);


  /*
    a2dp_sink.set_avrc_rn_playstatus_callback(avrc_rn_playstatus_callback);
    a2dp_sink.set_avrc_rn_play_pos_callback(avrc_rn_play_pos_callback, 5); //Update the playing position every 5 seconds when Playing
    a2dp_sink.set_avrc_rn_track_change_callback(avrc_rn_track_change_callback);
  */

  a2dp_sink.start("AVR-IBus-BT");

  delay(50); a2dp_sink.set_volume(0xFF);

}

void loop() {
  if (Serial.available()) {
    switch (Serial.read()) {
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
        break;

    }
  }
}
