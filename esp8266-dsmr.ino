#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPClient.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <ArduinoJson.h>
#include "ESP8266mDNS.h"

#include "MQTTPublisher.h"
#include "WifiConnector.h"
#include "Settings.h"
#include "Logger.h"
#include "AutoConfig.h"

typedef struct
{
  String name;
  String key; // OBIS property key
  int start;  // start of value in string
  int end;    // end  of value in string
  bool online;

  enum
  {
    STRING,
    FLOAT,
    INT
  } valueType;

} Measurement;

const Measurement measurements[] = {
    {"version", "1-3:0.2.8", 10, 12, false, Measurement::STRING},
    {"power/timestamp", "0-0:1.0.0", 10, 23, false, Measurement::STRING},
    {"power/device_id", "0-0:96.1.1", 11, 45, false, Measurement::STRING},
    {"power/consumption", "1-0:1.7.0", 10, 16, false, Measurement::FLOAT},
    {"power/production", "1-0:2.7.0", 10, 16, false, Measurement::FLOAT},
    {"power/total_consumption_tariff_1", "1-0:1.8.1", 10, 20, false, Measurement::FLOAT},
    {"power/total_consumption_tariff_2", "1-0:1.8.2", 10, 20, false, Measurement::FLOAT},
    {"power/total_production_tariff_1", "1-0:2.8.1", 10, 20, false, Measurement::FLOAT},
    {"power/total_production_tariff_2", "1-0:2.8.2", 10, 20, false, Measurement::FLOAT},
    {"power/power_tariff", "0-0:96.14.0", 12, 16, false, Measurement::INT},
    {"power/short_power_outages", "0-0:96.7.21", 12, 17, false, Measurement::INT},
    {"power/long_power_outages", "0-0:96.7.9", 11, 16, false, Measurement::INT},
    {"power/phase_1/short_power_drops", "1-0:32.32.0", 12, 17, false, Measurement::INT},
    {"power/phase_2/short_power_drops", "1-0:52.32.0", 12, 17, false, Measurement::INT},
    {"power/phase_3/short_power_drops", "1-0:72.32.0", 12, 17, false, Measurement::INT},
    {"power/phase_1/short_power_peaks", "1-0:32.36.0", 12, 17, false, Measurement::INT},
    {"power/phase_2/short_power_peaks", "1-0:52.36.0", 12, 17, false, Measurement::INT},
    {"power/phase_3/short_power_peaks", "1-0:72.36.0", 12, 17, false, Measurement::INT},
    {"power/phase_1/current", "1-0:31.7.0", 11, 14, false, Measurement::INT},
    {"power/phase_2/current", "1-0:51.7.0", 11, 14, false, Measurement::INT},
    {"power/phase_3/current", "1-0:71.7.0", 11, 14, false, Measurement::INT},
    {"power/phase_1/consumption", "1-0:21.7.0", 11, 17, false, Measurement::FLOAT},
    {"power/phase_2/consumption", "1-0:41.7.0", 11, 17, false, Measurement::FLOAT},
    {"power/phase_3/consumption", "1-0:61.7.0", 11, 17, false, Measurement::FLOAT},
    {"power/phase_1/production", "1-0:22.7.0", 11, 17, false, Measurement::FLOAT},
    {"power/phase_2/production", "1-0:42.7.0", 11, 17, false, Measurement::FLOAT},
    {"power/phase_3/production", "1-0:62.7.0", 11, 17, false, Measurement::FLOAT},
    {"gas/total", "0-1:24.2.1", 26, 35, false, Measurement::FLOAT},
    {"gas/device_id", "0-1:96.1.0", 11, 45, false, Measurement::STRING},
    {"gas/timestamp", "0-1:24.2.1", 11, 24, false, Measurement::STRING}};

MQTTPublisher mqttPublisher;
WifiConnector wifiConnector;
AutoConfig autoConfig;
WiFiUDP ntpUDP;
String incomingString = "";
bool hasMQTT = false;
bool hasWIFI = false;
Logger logger = Logger("App");
char identifier[24];
int valueState[29];

int rxPin = 3;
int lvlPin = 5;

void setup()
{
  // Start serial ESP8266 RX port (pin 3)
  Serial.begin(115200);
  pinMode(rxPin, FUNCTION_0); // RX

  logger.info("Start setup");

  // Set pin modes
  pinMode(lvlPin, OUTPUT);    // D1
  digitalWrite(lvlPin, HIGH); // Turn on RX Trans

  snprintf(identifier, sizeof(identifier), "ESP_DSMR_%X", ESP.getChipId());

  // Setup Wifi
  wifiConnector = WifiConnector();
  wifiConnector.start();

  // Setup MQTT
  mqttPublisher = MQTTPublisher(identifier);
  mqttPublisher.start();

  // Setup OTA
  ArduinoOTA.setHostname(WIFI_HOSTNAME);
  ArduinoOTA.begin();

  // Sent HA config
  autoConfig = AutoConfig(mqttPublisher, identifier);
  autoConfig.SendConfig();

  logger.info("Setup complete");
}

void loop()
{

  wifiConnector.handle();
  yield();
  ArduinoOTA.handle();
  yield();
  mqttPublisher.handle();
  yield();

  // If serial received, read until newline
  if (Serial.available() > 0)
  {
    incomingString = Serial.readStringUntil('\n');
    handleString(incomingString);
  }
}

// Regex are not supported, so use indexOf and substring
void handleString(String incomingString)
{

  int i;
  int arraySize = sizeof(measurements) / sizeof(measurements[0]);

  for (i = 0; i < arraySize; i++)
  {
    Measurement measurement = measurements[i];
    String obisKey = measurement.key;

    if (incomingString.indexOf(obisKey) > -1)
    {
      // found
      String value = incomingString.substring(measurement.start, measurement.end);
      logger.debug("DEBUG_1 " + obisKey + "=" + value);

      switch (measurement.valueType)
      {
      case Measurement::FLOAT:
        value = String(value.toFloat(), 3);
        break;
      case Measurement::INT:
        value = String(value.toInt());
        break;
      default:
        break;
      }

      // Check if measurement state is offline, if so publish online state
      if (!measurement.online)
      {
        measurement.online = true;
        mqttPublisher.publish(measurement.name + "/status", "online", true);
      }

      // Publish measurement
      mqttPublisher.publish(measurement.name, value, true);
    }
  }
}