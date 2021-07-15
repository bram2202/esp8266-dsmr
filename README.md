# esp8266-dsmr

A ESP8266 based DSMR reader, posting messages onto MQTT.<br/>
Can be powered directly from the meter itself, no external power supply needed*.<br/>
<sup><i>* if enough power can be supplied by the meter.</i></sup>

The code should work on DSRM v2.2 and higher, only tested on V4.2.<br/>
Supports Dutch and Belgian smart meters.<br/>

## Board in action
![esp8266-dsmr](/docs/PCB_IRL.png "esp8266-dsmr")

## Requirements 
* Arduino IDE / VS code
* ESP8266 board (Wemos/LOLIN D1 mini/ESP01/NodeMCU)
* Basic soldering and wiring skills
* (For Wemos d1 mini) CH340G driver [[link]](https://wiki.wemos.cc/downloads)
* Prototype board / breadboard / PCB
* RJ11/12/25 cable

## Library dependencies
- [PubSubClient](https://pubsubclient.knolleary.net) - MQTT client
- [Core for ESP8266](https://github.com/esp8266/Arduino) - Arduino core for ESP8266 WiFi chip

## Messages

### Info
| Name | unit | DSMR code | MQTT topic |
|:----  |:-------|:------ |:------|
| DSMR version | - | 1-3:0.2.8 | <MQTT_TOPIC>/version | 
| Status | online | - | <MQTT_TOPIC>/status | 

### Power
| Name | unit | DSMR code | MQTT topic |
|:----  |:-------|:------ |:------|
| current power consumption | kW | 1-0:1.7.0 | <MQTT_TOPIC>/power/consumption | 
| current power production | kW | 1-0:2.7.0 | <MQTT_TOPIC>/power/production | 
| total consumption tariff 1 | kWh | 1-0:1.8.1 | <MQTT_TOPIC>/power/total_consumption_tariff_1 |
| total consumption tariff 2 | kWh | 1-0:1.8.2 | <MQTT_TOPIC>/power/total_consumption_tariff_2 |
| total production tariff 1 | kWh | 1-0:2.8.1 | <MQTT_TOPIC>/power/total_production_tariff_1 |
| total production tariff 2 | kWh | 1-0:2.8.2 | <MQTT_TOPIC>/power/total_production_tariff_2 |
| power tariff | [See tariffs](#tariffs) | 0-0:96.14.0 | <MQTT_TOPIC>/power/power_tariff |
| short power outages | - | 0-0:96.7.21 |<MQTT_TOPIC>/power/short_power_outages |
| long power outages | - | 0-0:96.7.9 |<MQTT_TOPIC>/power/long_power_outages |
| instant current phase 1 | A | 1-0:31.7.0 |<MQTT_TOPIC>/power/phase_1/current |
| instant current phase 2 | A | 1-0:51.7.0 |<MQTT_TOPIC>/power/phase_2/current |
| instant current phase 3 | A | 1-0:71.7.0 |<MQTT_TOPIC>/power/phase_3/current |
| instant usage phase 1 | kW | 1-0:21.7.0 |<MQTT_TOPIC>/power/phase_1/usage |
| instant usage phase 2 | kW | 1-0:41.7.0 |<MQTT_TOPIC>/power/phase_2/usage |
| instant usage phase 3 | kW | 1-0:61.7.0 |<MQTT_TOPIC>/power/phase_3/usage |
| instant delivery phase 1 | kW | 1-0:22.7.0 |<MQTT_TOPIC>/power/phase_1/delivery |
| instant delivery phase 2 | kW | 1-0:42.7.0 |<MQTT_TOPIC>/power/phase_2/delivery |
| instant delivery phase 3 | kW | 1-0:62.7.0 |<MQTT_TOPIC>/power/phase_3/delivery |
| short drops phase 1 | - | 1-0:32.32.0 | <MQTT_TOPIC>/power/phase_1/drops |
| short drops phase 2 | - | 1-0:52.32.0 | <MQTT_TOPIC>/power/phase_2/drops |
| short drops phase 3 | - | 1-0:72.32.0 | <MQTT_TOPIC>/power/phase_3/drops |
| short peaks phase 1 | - | 1-0:32.36.0 | <MQTT_TOPIC>/power/phase_1/peaks |
| short peaks phase 2 | - | 1-0:52.36.0 | <MQTT_TOPIC>/power/phase_2/peaks |
| short peaks phase 3 | - | 1-0:72.36.0 | <MQTT_TOPIC>/power/phase_3/peaks |
| timestamp| - | 0-0:1.0.0 | <MQTT_TOPIC>/power/timestamp |
| device id | - | 0-0:96.1.1 | <MQTT_TOPIC>/power/device |

### Gas
| Name | unit | DSMR code | MQTT topic |
|:----  |:-------|:------ |:------|
| total gas | m3 | 0-1:24.2.1 | <MQTT_TOPIC>/gas/total |
| timestamp| - | 0-1:24.2.1| <MQTT_TOPIC>/gas/timestamp |
| device id | - | 0-1:96.1.0 | <MQTT_TOPIC>/gas/device |

## Tariffs
The meter has a power tariff property, and is used for the total consumption/production counters.<br/>
The values for the day and night tariffs are different in the Netherlands compared to Belgium.
| Country | tariff | value |
|:---- |:---- |:---- |
| NL | Night (low) | tariff_1 |
| NL | Day (high) | tariff_2 |
| BE | Night (low) |tariff_2 |
| BE | Day (high)| tariff_1 |

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
View [scheme (pdf)](https://github.com/bram2202/esp8266-dsmr/blob/master/PCB/schematic.pdf).

Using a level shifter inverter to get the serial output from the meter into the ESP.<br>
The board can be powered directly from the meters power supply <i>(this can vary between models)</i>.


## Custom PCB
Create your own with the [Gerber files (zip)](https://github.com/bram2202/esp8266-dsmr/blob/master/PCB/gerber.zip)


## PCB case
I designed a case to be 3D printed, it fits the board loosely, and is meant to be glued shut

![esp8266-dsmr](/docs/case_1.jpg "esp8266-dsmr case")

STL files are found in the [STL folder](https://github.com/bram2202/esp8266-dsmr/tree/master/STL)

## Parts
| Type | Amount |
|:---|:---|
| ESP8266 board| 1 |
| Prototyping board or PCB | 1 |
| 2.2k resistor (0805) | 2 |
| 1k resistor (0805) | 1 |
| BC547 or BC817 (SOT-23) | 2 | 
| 470uf cap. 8x12mm | 1 | 

## DSMR connection

Connecting to the DSMR with a RJ11/12/25 (6p6c or 6p4c) cable plugged into the Port 1 (P1), found on all supported smart meters.

| DSRM P1 | Description | PCB Pin |
|:---|:---|:---|
| 1* | +5v | 6 (5v) |
| 2 | Request | 5 (5v) |
| 3 | Data GND| 4 (GND) |
| 4 | N.C. | N.C. |
| 5 | Data | 2 (Data)|
| 6* | Power GND | 1 (GND) |

`* 1 and 6 are not needed if powered by USB.`

## Known issues
- Some DSMR cannot deliver enough power to run the Wemos stably.<br> 
Connect a 5V usb supply to fix this.
