# esp8266-dsmr

A ESP8266 based DSMR reader, posting onto MQTT, powered directly from the meter itself, no external power supply needed..

All units (except power tariff and version) are rounded to 3 decimals.

The code should work on DSRM v2.2 and higher, only tested on V4.2.

![esp8266-dsmr](https://github.com/bram2202/esp8266-dsmr/blob/master/docs/esp8266-dsmr.jpg "esp8266-dsmr")

## Requirements 
* ESP8266 (Wemos/LOLIN D1 mini/ESP01/NodeMCU)
* Basic soldering and wiring skills
* Arduino core for ESP8266 WiFi chip [[link]](https://github.com/esp8266/Arduino)
* (For Wemos d1 mini) CH340G driver [[link]](https://wiki.wemos.cc/downloads)
* Arduino IDE
* Hardware package for arduino [[LINK]](https://github.com/esp8266/Arduino)

## Library dependencies
- [PubSubClient](https://pubsubclient.knolleary.net) - MQTT client
- [WifiManager](https://github.com/esp8266/Arduino) - Wifi client

## Supported messages

### Info
| Name | unit | DSMR code | MQTT topic |
|:----  |:-------|:------ |:------|
| DSMR version | - | 1-3:0.2.8 | <MQTT_TOPIC>/version | 
| Status | online, offline | - | <MQTT_TOPIC>/status | 

### Power
| Name | unit | DSMR code | MQTT topic |
|:----  |:-------|:------ |:------|
| current power consumption | kW | 1-0:1.7.0 | <MQTT_TOPIC>/power/consumption | 
| current power production | kW | 1-0:2.7.0 | <MQTT_TOPIC>/power/production | 
| total consumption low | kWh | 1-0:1.8.1 | <MQTT_TOPIC>/power/total_consumption_low |
| total consumption high | kWh | 1-0:1.8.2 | <MQTT_TOPIC>/power/total_consumption_high |
| total production low | kWh | 1-0:2.8.1 | <MQTT_TOPIC>/power/total_production_low |
| total production high | kWh | 1-0:2.8.2 | <MQTT_TOPIC>/power/total_production_high |
| power tariff | 1 = low, 2 = high | 0-0:96.14.0 | <MQTT_TOPIC>/power/power_tariff |
| short power outages | - | 0-0:96.7.21 |<MQTT_TOPIC/>/power/short_power_outages |
| long power outages | - | 0-0:96.7.9 |<MQTT_TOPIC/>/power/long_power_outages |
| instant current phase 1 | A | 1-0:31.7.0 |<MQTT_TOPIC/>/power/phase_1/current |
| instant current phase 2 | A | 1-0:51.7.0 |<MQTT_TOPIC/>/power/phase_2/current |
| instant current phase 3 | A | 1-0:71.7.0 |<MQTT_TOPIC/>/power/phase_3/current |
| instant usage phase 1 | kW | 1-0:21.7.0 |<MQTT_TOPIC/>/power/phase_1/usage |
| instant usage phase 2 | kW | 1-0:41.7.0 |<MQTT_TOPIC/>/power/phase_2/usage |
| instant usage phase 3 | kW | 1-0:61.7.0 |<MQTT_TOPIC/>/power/phase_3/usage |
| instant delivery phase 1 | kW | 1-0:22.7.0 |<MQTT_TOPIC/>/power/phase_1/delivery |
| instant delivery phase 2 | kW | 1-0:42.7.0 |<MQTT_TOPIC/>/power/phase_2/delivery |
| instant delivery phase 3 | kW | 1-0:62.7.0 |<MQTT_TOPIC/>/power/phase_3/delivery |
| short drops phase 1 | - | 1-0:32.32.0 | <MQTT_TOPIC/>/power/phase_1/drops |
| short drops phase 2 | - | 1-0:52.32.0 | <MQTT_TOPIC/>/power/phase_2/drops |
| short drops phase 3 | - | 1-0:72.32.0 | <MQTT_TOPIC/>/power/phase_3/drops |
| short peaks phase 1 | - | 1-0:32.36.0 | <MQTT_TOPIC/>/power/phase_1/peaks |
| short peaks phase 2 | - | 1-0:52.36.0 | <MQTT_TOPIC/>/power/phase_2/peaks |
| short peaks phase 3 | - | 1-0:72.36.0 | <MQTT_TOPIC/>/power/phase_3/peaks |
| timestamp| - | 0-0:1.0.0 | <MQTT_TOPIC/>/power/timestamp |
| device id | - | 0-0:96.1.1 | <MQTT_TOPIC/>/power/device |

### Gas
| Name | unit | DSMR code | MQTT topic |
|:----  |:-------|:------ |:------|
| total gas | m3 | 0-1:24.2.1 | <MQTT_TOPIC>/gas/total |
| timestamp| - | 0-1:24.2.1| <MQTT_TOPIC/>/gas/timestamp |
| device id | - | 0-1:96.1.0 | <MQTT_TOPIC/>/gas/device |


## Settings
Copy `Settings.example.h` to `Settings.h` and fill in the correct data.

| Setting | default | Description|  
|:------------- |:----- |:-------------:| 
| WIFI_HOSTNAME | ESP-DSMR | device name on network |
| WIFI_SSID | - | Wifi name to connect to |
| WIFI_PASSWORD | - | Wifi password |
| MQTT_HOST_NAME | - | MQTT broker address |
| MQTT_PORT | 1833 | MQTT broker port |
| MQTT_USER_NAME| - | MQTT user name |
| MQTT_PASSWORD | - | MQTT password |
| MQTT_HOSTNAME| ESP-DSMR | MQTT name |
| MQTT_PREFIX | dsmr | MQTT prefix |
| USE_CLIENT_ID | FALSE | Use clientId in prefix |
| LOG_LEVEL | INFO | ( DEBUG / INFO / WARN ) |


## Circuit
view [scheme.pdf](scheme.pdf).

Using a level shifter inverter to get the serial output from the meter into the ESP.<br>
The board is powered directly from the meters power supply.<br>

**Flash the firmware before attaching the circuit,** see "know issue"!

### Parts
| Type | Amount |
|:---|:---|
| ESP8266 | 1 |
| Prototyping board | 1 |
| 2.2k resistor | 2 |
| 1k resistor | 1 |
| BC547 | 1 | 
| 470uf cap. | 1 | 

### RJ11 connection

Connecting to the DSMR witn a RJ11 in Port 1 (P1), found on most smart meters.


| DSRM RJ11 | Description | J1 pin |
|:---|:---|:---|
| 1 | +5v | 1 (5v) |
| 2 | Request | 2 (5v) |
| 3 | Data GND| 3 (GND) |
| 4 | N.C. | N.C. |
| 5 | Data | 5 (Data)|
| 6 | Power GND | 6 (GND) |


## Known issues
- If the level shifter inverter is connected, it's impossible to flash the firmware.<br>
Pin RX is used, disconnect the pin to flash new firmware.
- Some DSMR cannot deliver enough power to run the Wemos stably.<br> 
Connect a 5V usb supply to fix this.
