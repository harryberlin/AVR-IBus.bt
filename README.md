# AVR-IBus.A2DP<br>`BT A2DP Extension for AVR-IBus Modul`
## Description
This will get an Extension Board for [AVR-IBus.public](https://github.com/harryberlin/AVR-IBus.public) Basic Modul.
To use the BMW Radio Mode [CD] as Bluetooth Audio Device.
<br>Steps:
- design Extension PCB ![5%](https://progress-bar.dev/05)
- code ESP32 Code for Bluetooth A2DP ![35%](https://progress-bar.dev/35)
- Side ESP32: code Communication with Atmega2560 ![40%](https://progress-bar.dev/40)
- Side Atmega2560: code Communication with ESP32 ![40%](https://progress-bar.dev/40)

## BOM
- ESP32
- PCM5102A
- ...

## Wiring
<img src="docs/connection_schema.png"  border="1" width="250">

## Commands & States
<details>
	<summary>show</summary>
	
| Command    | Description                 |
| ---------- | --------------------------- |
| `CQ`       | Connection state Request    |
|            |                             |
| `MQ`       | Music state Request         |
| `MS`       | Music Stop                  |
| `MH`       | Music Pause                 |
| `MM`       | Music Play                  |
| `MP`       | Music Previous Track        |
| `MR`       | Music Fast Rewind           |
| `MF`       | Music Fast Forward          |
| `MN`       | Music Next Track            |
| `MQ`       | Music sate request          |
| `MQ`       | Music sate request          |

| States     | Description                 |
| ---------- | --------------------------- |
| `C0`       | Disconnected                |
| `C1`       | Connecting                  |
| `C2`       | Connected                   |
| `CA`       | Returns connected Mac-Address <br>`example CA:11:22:33:44:55:66`|
|            |                             |
| `M0`       | Music is stopped  or paused |
| `M1`       | Music is playing            |
| `M2`       | Music skips prev Track or back |
| `M3`       | Music fast rewind Track     |
| `M4`       | Music fast forward Track    |
| `M5`       | Music skips next Track      |

</details>


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
