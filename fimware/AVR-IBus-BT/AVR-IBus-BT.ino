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
#define ANALOG_OUTPUT //just for simple testing with headphone directly

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
#ifdef ANALOG_OUTPUT
AnalogAudioStream out;
#else
I2SStream out;
#endif

//#include "BluetoothA2DPSink.h"
//BluetoothA2DPSink a2dp_sink(out);

#include "BluetoothA2DPSinkQueued.h"
BluetoothA2DPSinkQueued a2dp_sink(out);

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

uint8_t bt_mac_address[6] = {0, 0, 0, 0, 0, 0};

const PROGMEM uint8_t FIRST_SETUP = 0;
const PROGMEM uint8_t BT_PIN = 1;
const PROGMEM uint8_t BT_NAME = 101;


const PROGMEM uint8_t STOP = 0; // MS
const PROGMEM uint8_t PLAY = 1; // MM
const PROGMEM uint8_t PREV = 2; // MP
const PROGMEM uint8_t FRWD = 3; // MR
const PROGMEM uint8_t FFWD = 4; // MF
const PROGMEM uint8_t NEXT = 5; // MN

uint8_t MusicState = STOP;

// Function Declaration

void audio_state_changed(esp_a2d_audio_state_t state, void *ptr);
void avrc_rn_playstatus_callback(esp_avrc_playback_stat_t playback);
void connection_state_changed(esp_a2d_connection_state_t state, void *ptr);
void settings_btname_set(String sentence, boolean commit = false);
