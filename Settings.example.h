// Hostname of ESP8266
#define WIFI_HOSTNAME "ESP-DSMR"

// Wifi SSID to connect to
#define WIFI_SSID "<wifi name>"

// Passowrd for WIFI
#define WIFI_PASSWORD "<wifi password>"

// Set the mqqt host name or ip address to your mqqt host. Leave empty to disable mqtt.
#define MQTT_BROKER "<MQTT broker address>"

// Mqtt port for the above host
#define MQTT_PORT 1883

// If authentication is enabled for mqtt, set the username below. Leave empty to disable authentication
#define MQTT_USER_NAME "<MQTT user name>"

// Password for above user
#define MQTT_PASSWORD "<MQTT password>"

// Setup gas entity in HA
#define AUTOCONFIG_GAS true

// Setup all power entities in HA
#define AUTOCONFIG_POWER_EXTENDED true

// Setup all custom entities in HA
#define AUTOCONFIG_CUSTOM_POWER_EXTENDED true

//for debugging, print info on serial (DEBUG, INFO, WARN)
#define LOG_LEVEL INFO
