# esp8266-dsmr
A ESP8266 based DSMR reader, posting onto MQTT, powered directly from the meter itself, no external power supply needed..

All units (except power tariff and version) are rounded to 3 decimals.

The code should work on DSRM v2.2 and higher, only tested on V4.2.

## Requirements 
* ESP8266 (Wemos/LOLIN D1 mini)
* Basic soldering and wiring skills
* (For Wemos d1 mini) CH340G driver [[link]](https://wiki.wemos.cc/downloads)
* Arduino IDE
* Hardware package for arduino [[LINK]](https://github.com/esp8266/Arduino)
* MQTT lib. for Arduino [[LINK]](https://pubsubclient.knolleary.net/)


## Supported messages
| Name | unit | DSMR code | MQTT topic |
|:----  |:-------|:------ |:------|
| DSMR version | - | 0.2.8 | dsmr/power_consuption | 
| power consuption | kW | 1.7.0 | dsmr/power_consuption | 
| power prduction | kW | 2.7.0| dsmr/power_production | 
| total consuption low | kWh | 1.8.1 | dsmr/total_consuption_low |
| total consuption high | kWh | 1.8.2 | dsmr/total_consuption_high |
| total production low | kWh | 2.8.1 | dsmr/total_production_low |
| total production high | kWh | 2.8.2 | dsmr/total_production_high |
| total gas | m3 | 24.2.1 | dsmr/total_gas |
| power tariff | 1 = low, 2 = high | 96.14.0 | dsmr/power_tariff |

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
| MQTT_TOPIC | dsmr | MQTT topic prefix |
| DEBUGE_MODE | true | debug mode |


## Circuit
view [scheme.pdf](scheme.pdf).

Using a level shifter inverter to get the serial output from the meter into the ESP.
The board is powered directly from the meters power supply.

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
