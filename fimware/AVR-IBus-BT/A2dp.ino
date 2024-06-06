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



// for esp_a2d_audio_state_t see https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/bluetooth/esp_a2dp.html#_CPPv421esp_a2d_audio_state_t
void audio_state_changed(esp_a2d_audio_state_t state, void *ptr) {
  Serial.print(state, HEX);
  Serial.print("audio_state_changed::");
  Serial.println(a2dp_sink.to_str(state));
}

///TESTTTTTTTT
void avrc_rn_play_pos_callback(uint32_t play_pos) {
  Serial.printf("Play position is %d (%d seconds)\n", play_pos, (int)round(play_pos / 1000.0));
}

void avrc_rn_playstatus_callback(esp_avrc_playback_stat_t playback) {
  //Serial.print(playback, HEX);
  //Serial.print("avrc_rn_playstatus_callback::");
  //Serial.println(a2dp_sink.to_str(playback));  
  
  switch (playback) {
    case esp_avrc_playback_stat_t::ESP_AVRC_PLAYBACK_STOPPED:
      Serial.println("Stopped.");
      setPlaybackState(STOP);
      break;
    case esp_avrc_playback_stat_t::ESP_AVRC_PLAYBACK_PLAYING:
      Serial.println("Playing.");
      setPlaybackState(PLAY);
      break;
    case esp_avrc_playback_stat_t::ESP_AVRC_PLAYBACK_PAUSED:
      Serial.println("Paused.");
      setPlaybackState(STOP);
      break;
    case esp_avrc_playback_stat_t::ESP_AVRC_PLAYBACK_FWD_SEEK:
      Serial.println("Forward seek.");
      setPlaybackState(FFWD);
      break;
    case esp_avrc_playback_stat_t::ESP_AVRC_PLAYBACK_REV_SEEK:
      Serial.println("Reverse seek.");
      setPlaybackState(FRWD);
      break;
    case esp_avrc_playback_stat_t::ESP_AVRC_PLAYBACK_ERROR:
      Serial.println("Error.");
      setPlaybackState(STOP);
      break;
    default:
      Serial.printf("Got unknown playback status %d\n", playback);
  }
  printPlaybackState();
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
  #ifndef ANALOG_OUTPUT
  auto cfg = out.defaultConfig();
  cfg.pin_bck = 26;
  cfg.pin_ws = 25;
  cfg.pin_data = 22;
  out.begin(cfg);
  #endif


  a2dp_sink.set_on_connection_state_changed(connection_state_changed);
  //a2dp_sink.set_on_audio_state_changed(audio_state_changed);


  a2dp_sink.set_avrc_rn_playstatus_callback(avrc_rn_playstatus_callback);
  //a2dp_sink.set_avrc_rn_play_pos_callback(avrc_rn_play_pos_callback, 5); //Update the playing position every 5 seconds when Playing
  //a2dp_sink.set_avrc_rn_track_change_callback(avrc_rn_track_change_callback);


  a2dp_sink.set_auto_reconnect(true);

  a2dp_sink.start(settings_btname_get().c_str());
  a2dp_sink.pause();

  
  printPlaybackState();

}


void setPlaybackState(uint8_t state){
  if (state == STOP && MusicState > PLAY) return;
  MusicState = state;
}

void printPlaybackState() {
  Serial.printf("M%d\r\n", MusicState );
  Serial1.printf("M%d\r\n", MusicState );
}
