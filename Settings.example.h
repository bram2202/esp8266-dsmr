//Hostname of ESP8266
#define WIFI_HOSTNAME "ESP-DSMR"

//Wifi SSID to connect to
#define WIFI_SSID "<wifi name>"

//Passowrd for WIFI
#define WIFI_PASSWORD "<wifi password>"

//set the mqqt host name or ip address to your mqqt host. Leave empty to disable mqtt.
#define MQTT_HOST_NAME "<MQTT broker>"

//mqtt port for the above host
#define MQTT_PORT 1883

//if authentication is enabled for mqtt, set the username below. Leave empty to disable authentication
#define MQTT_USER_NAME "<MQTT user name>"

//password for above user
#define MQTT_PASSWORD "<MQTT password>"

//publish online status name
#define MQTT_HOSTNAME "ESP-DSMR"

//default MQTT prefix
#define MQTT_PREFIX "dsmr"

// Use Client ID in MQTT prefix
#define USE_CLIENT_ID false

//for debugging, print info on serial (DEBUG, INFO, WARN)
#define LOG_LEVEL INFO
