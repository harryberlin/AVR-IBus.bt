# AVR-IBus.A2DP<br>`BT A2DP Extension for AVR-IBus Modul`
## Description
This will get an Extension Board for [AVR-IBus.public](https://github.com/harryberlin/AVR-IBus.public) Basic Modul.
To use the BMW Radio Mode [CD] as Bluetooth Audio Device.
<br>Steps:
- design Extension PCB ![5%](https://progress-bar.dev/05)
- code ESP32 Code for Bluetooth A2DP ![20%](https://progress-bar.dev/20)
- Side ESP32: code Communication with Atmega2560 ![20%](https://progress-bar.dev/20)
- Side Atmega2560: code Communication with ESP32 ![10%](https://progress-bar.dev/20)

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

## Project Progress/Milestones
<details>
<summary>show</summary>
<img src="docs/01_1st_tests.jpeg"  border="1" width="250"><br>
<img src="docs/02_1st_tests.jpeg"  border="1" width="250">
</details>
