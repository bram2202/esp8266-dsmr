#include "MQTTPublisher.h"
#include "Settings.h"
#include "Logger.h"

#pragma once

namespace AutoConfig
{
Logger logger;

void SendConfig(MQTTPublisher mqttPublisher, char identifier[24])
{
  logger = Logger("AutoConfig");
  logger.info("Start auto config");

  char mqttPayload[2048];
  DynamicJsonDocument device(256);
  DynamicJsonDocument autoconfPayload(1024);
  StaticJsonDocument<64> identifiersDoc;
  JsonArray identifiers = identifiersDoc.to<JsonArray>();

  // Set device properties
  identifiers.add(identifier);
  device["identifiers"] = identifiers;
  device["manufacturer"] = "Bram2202";
  device["model"] = "ESP - DSMR";
  device["name"] = identifier;
  device["sw_version"] = "v1.3.0";

  // Set sensor properties
  mqttPublisher.publish("test", "test", true);

  // power_consumption
  autoconfPayload["device"] = device.as<JsonObject>();
  autoconfPayload["availability_topic"] = String(identifier) + "/power/consumption/status";
  autoconfPayload["state_topic"] = String(identifier) + "/power/consumption";
  autoconfPayload["name"] = String(identifier) + "_power_consumption";
  autoconfPayload["unit_of_measurement"] = "kW";
  autoconfPayload["unique_id"] = "power_consumption";
  autoconfPayload["icon"] = "mdi:flash";
  autoconfPayload["device_class"] = "power";
  autoconfPayload["state_class"] = "measurement";
  serializeJson(autoconfPayload, mqttPayload);
  mqttPublisher.publish("homeassistant/sensor/" + String(identifier) + "/power_consumption/config", &mqttPayload[0], false);

  autoconfPayload.clear();
  logger.info("1st send");

  // power_production
  autoconfPayload["device"] = device.as<JsonObject>();
  autoconfPayload["availability_topic"] = String(identifier) + "/power/production/status";
  autoconfPayload["state_topic"] = String(identifier) + "/power/production";
  autoconfPayload["name"] = String(identifier) + "_power_production";
  autoconfPayload["unit_of_measurement"] = "kW";
  autoconfPayload["unique_id"] = "power_production";
  autoconfPayload["icon"] = "mdi:flash";
  autoconfPayload["device_class"] = "power";
  autoconfPayload["state_class"] = "measurement";
  serializeJson(autoconfPayload, mqttPayload);
  mqttPublisher.publish("homeassistant/sensor/" + String(identifier) + "/power_production/config", &mqttPayload[0], false);

  autoconfPayload.clear();
  logger.info("2nd send");
}
}
