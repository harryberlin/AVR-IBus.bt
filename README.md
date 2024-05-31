# AVR-IBus.A2DP<br>`BT A2DP Extension for AVR-IBus Modul`
## Description
This will get an Extension Board for [AVR-IBus.public](https://github.com/harryberlin/AVR-IBus.public).
To use the BMW Radio Mode [CD] as Bluetooth Audio Device.
<br>Steps:
- design Extension PCB ![5%](https://progress-bar.dev/05)
- code ESP32 Code for Bluetooth A2DP ![10%](https://progress-bar.dev/10)
- Side ESP32: code Communication with Atmega2560 ![0%](https://progress-bar.dev/00)
- Side Atmega2560: code Communication with ESP32 ![10%](https://progress-bar.dev/10)

## BOM
- ESP32
- PCM5102A
- ...

## Wiring
<img src="docs/connection_schema.png"  border="1" width="250">

## Used Librarys:
- [ESP32-A2DP](https://github.com/pschatzmann/ESP32-A2DP) by pschatzmann
- [arduino-audio-tools](https://github.com/pschatzmann/arduino-audio-tools) by pschatzmann
- Arduino
- ESP32 Package by Espressif

