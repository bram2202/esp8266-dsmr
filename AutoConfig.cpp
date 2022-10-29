#include <ArduinoJson.h>
#include "MQTTPublisher.h"
#include "AutoConfig.h"
#include "Settings.h"
#include "Logger.h"

#pragma once

/**
 * instantiate AutoConfig class.
 *  *
 * @param mqttPublisher Publisher for sending msgs
 * @param identifier ESP identifier
 */
AutoConfig::AutoConfig(MQTTPublisher &mqttPublisher, String identifier)
{
    _mqttPublisher = mqttPublisher;
    _identifier = identifier;
    logger = Logger("AutoConfig");
}

AutoConfig::AutoConfig() {}

/**
 * Send sensor config for Home Assistant 
 */
void AutoConfig::SendConfig()
{
    logger = Logger("AutoConfig");
    logger.info("Start auto config");

    char mqttPayload[2048];
    DynamicJsonDocument device(256);
    DynamicJsonDocument autoconfPayload(1024);
    StaticJsonDocument<64> identifiersDoc;
    JsonArray identifiers = identifiersDoc.to<JsonArray>();

    // Set device properties
    identifiers.add(_identifier);
    device["identifiers"] = identifiers;
    device["manufacturer"] = "Bram2202";
    device["model"] = "ESP-DSMR";
    device["name"] = _identifier;
    device["sw_version"] = "v1.3.1_u3";

    // power_consumption
    autoconfPayload["device"] = device.as<JsonObject>();
    autoconfPayload["availability_topic"] = _identifier + "/power/consumption/status";
    autoconfPayload["state_topic"] = _identifier + "/power/consumption";
    autoconfPayload["name"] = _identifier + "_power_consumption";
    autoconfPayload["unit_of_measurement"] = "kW";
    autoconfPayload["unique_id"] = "power_consumption";
    autoconfPayload["icon"] = "mdi:flash";
    autoconfPayload["device_class"] = "power";
    autoconfPayload["state_class"] = "measurement";
    serializeJson(autoconfPayload, mqttPayload);
    _mqttPublisher.publish("homeassistant/sensor/" + _identifier + "/power_consumption/config", &mqttPayload[0], false);
    autoconfPayload.clear();

    // power_production
    autoconfPayload["device"] = device.as<JsonObject>();
    autoconfPayload["availability_topic"] = _identifier + "/power/production/status";
    autoconfPayload["state_topic"] = _identifier + "/power/production";
    autoconfPayload["name"] = _identifier + "_power_production";
    autoconfPayload["unit_of_measurement"] = "kW";
    autoconfPayload["unique_id"] = "power_production";
    autoconfPayload["icon"] = "mdi:flash";
    autoconfPayload["device_class"] = "power";
    autoconfPayload["state_class"] = "measurement";
    serializeJson(autoconfPayload, mqttPayload);
    _mqttPublisher.publish("homeassistant/sensor/" + _identifier + "/power_production/config", &mqttPayload[0], false);
    autoconfPayload.clear();

    // total_consumption_tariff_1
    autoconfPayload["device"] = device.as<JsonObject>();
    autoconfPayload["availability_topic"] = _identifier + "/power/total_consumption_tariff_1/status";
    autoconfPayload["state_topic"] = _identifier + "/power/total_consumption_tariff_1";
    autoconfPayload["name"] = _identifier + "_total_consumption_tariff_1";
    autoconfPayload["unit_of_measurement"] = "kWh";
    autoconfPayload["unique_id"] = "total_consumption_tariff_1";
    autoconfPayload["icon"] = "mdi:counter";
    autoconfPayload["device_class"] = "energy";
    autoconfPayload["state_class"] = "total_increasing";
    serializeJson(autoconfPayload, mqttPayload);
    _mqttPublisher.publish("homeassistant/sensor/" + _identifier + "/total_consumption_tariff_1/config", &mqttPayload[0], false);
    autoconfPayload.clear();

    // total_consumption_tariff_2
    autoconfPayload["device"] = device.as<JsonObject>();
    autoconfPayload["availability_topic"] = _identifier + "/power/total_consumption_tariff_2/status";
    autoconfPayload["state_topic"] = _identifier + "/power/total_consumption_tariff_2";
    autoconfPayload["name"] = _identifier + "_total_consumption_tariff_2";
    autoconfPayload["unit_of_measurement"] = "kWh";
    autoconfPayload["unique_id"] = "total_consumption_tariff_2";
    autoconfPayload["icon"] = "mdi:counter";
    autoconfPayload["device_class"] = "energy";
    autoconfPayload["state_class"] = "total_increasing";
    serializeJson(autoconfPayload, mqttPayload);
    _mqttPublisher.publish("homeassistant/sensor/" + _identifier + "/total_consumption_tariff_2/config", &mqttPayload[0], false);
    autoconfPayload.clear();

    // total_production_tariff_1
    autoconfPayload["device"] = device.as<JsonObject>();
    autoconfPayload["availability_topic"] = _identifier + "/power/total_production_tariff_1/status";
    autoconfPayload["state_topic"] = _identifier + "/power/total_production_tariff_1";
    autoconfPayload["name"] = _identifier + "_total_production_tariff_1";
    autoconfPayload["unit_of_measurement"] = "kWh";
    autoconfPayload["unique_id"] = "total_production_tariff_1";
    autoconfPayload["icon"] = "mdi:counter";
    autoconfPayload["device_class"] = "energy";
    autoconfPayload["state_class"] = "total_increasing";
    serializeJson(autoconfPayload, mqttPayload);
    _mqttPublisher.publish("homeassistant/sensor/" + _identifier + "/total_production_tariff_1/config", &mqttPayload[0], false);
    autoconfPayload.clear();

    // total_production_tariff_2
    autoconfPayload["device"] = device.as<JsonObject>();
    autoconfPayload["availability_topic"] = _identifier + "/power/total_production_tariff_2/status";
    autoconfPayload["state_topic"] = _identifier + "/power/total_production_tariff_2";
    autoconfPayload["name"] = _identifier + "_total_production_tariff_2";
    autoconfPayload["unit_of_measurement"] = "kWh";
    autoconfPayload["unique_id"] = "total_production_tariff_2";
    autoconfPayload["icon"] = "mdi:counter";
    autoconfPayload["device_class"] = "energy";
    autoconfPayload["state_class"] = "total_increasing";
    serializeJson(autoconfPayload, mqttPayload);
    _mqttPublisher.publish("homeassistant/sensor/" + _identifier + "/total_production_tariff_2/config", &mqttPayload[0], false);
    autoconfPayload.clear();

    // power_tariff
    autoconfPayload["device"] = device.as<JsonObject>();
    autoconfPayload["availability_topic"] = _identifier + "/power/power_tariff/status";
    autoconfPayload["state_topic"] = _identifier + "/power/power_tariff";
    autoconfPayload["name"] = _identifier + "_power_tariff";
    autoconfPayload["unique_id"] = "power_tariff";
    serializeJson(autoconfPayload, mqttPayload);
    _mqttPublisher.publish("homeassistant/sensor/" + _identifier + "/power_tariff/config", &mqttPayload[0], false);
    autoconfPayload.clear();

    // Custom stuff here
    if (AUTOCONFIG_CUSTOM_POWER_EXTENDED)
    {
        // total_consumption
        autoconfPayload["device"] = device.as<JsonObject>();
        autoconfPayload["availability_topic"] = _identifier + "/power/total_consumption/status";
        autoconfPayload["state_topic"] = _identifier + "/power/total_consumption";
        autoconfPayload["name"] = _identifier + "_total_consumption";
        autoconfPayload["unit_of_measurement"] = "kWh";
        autoconfPayload["unique_id"] = "total_consumption";
        autoconfPayload["icon"] = "mdi:counter";
        autoconfPayload["device_class"] = "energy";
        autoconfPayload["state_class"] = "total_increasing";
        serializeJson(autoconfPayload, mqttPayload);
        _mqttPublisher.publish("homeassistant/sensor/" + _identifier + "/total_consumption/config", &mqttPayload[0], false);
        autoconfPayload.clear();

        // total_production
        autoconfPayload["device"] = device.as<JsonObject>();
        autoconfPayload["availability_topic"] = _identifier + "/power/total_production/status";
        autoconfPayload["state_topic"] = _identifier + "/power/total_production";
        autoconfPayload["name"] = _identifier + "_total_production";
        autoconfPayload["unit_of_measurement"] = "kWh";
        autoconfPayload["unique_id"] = "total_production";
        autoconfPayload["icon"] = "mdi:counter";
        autoconfPayload["device_class"] = "energy";
        autoconfPayload["state_class"] = "total_increasing";
        serializeJson(autoconfPayload, mqttPayload);
        _mqttPublisher.publish("homeassistant/sensor/" + _identifier + "/total_production/config", &mqttPayload[0], false);
        autoconfPayload.clear();

        // total_reactive_consumption
        autoconfPayload["device"] = device.as<JsonObject>();
        autoconfPayload["availability_topic"] = _identifier + "/power/total_reactive_consumption/status";
        autoconfPayload["state_topic"] = _identifier + "/power/total_reactive_consumption";
        autoconfPayload["name"] = _identifier + "_total_reactive_consumption";
        autoconfPayload["unit_of_measurement"] = "kWh";
        autoconfPayload["unique_id"] = "total_reactive_consumption";
        autoconfPayload["icon"] = "mdi:counter";
        autoconfPayload["device_class"] = "energy";
        autoconfPayload["state_class"] = "total_increasing";
        serializeJson(autoconfPayload, mqttPayload);
        _mqttPublisher.publish("homeassistant/sensor/" + _identifier + "/total_reactive_consumption/config", &mqttPayload[0], false);
        autoconfPayload.clear();

        // total_reactive_production
        autoconfPayload["device"] = device.as<JsonObject>();
        autoconfPayload["availability_topic"] = _identifier + "/power/total_reactive_production/status";
        autoconfPayload["state_topic"] = _identifier + "/power/total_reactive_production";
        autoconfPayload["name"] = _identifier + "_total_reactive_production";
        autoconfPayload["unit_of_measurement"] = "kWh";
        autoconfPayload["unique_id"] = "total_reactive_production";
        autoconfPayload["icon"] = "mdi:counter";
        autoconfPayload["device_class"] = "energy";
        autoconfPayload["state_class"] = "total_increasing";
        serializeJson(autoconfPayload, mqttPayload);
        _mqttPublisher.publish("homeassistant/sensor/" + _identifier + "/total_reactive_production/config", &mqttPayload[0], false);
        autoconfPayload.clear();

        // instantaneous current phase 1
        autoconfPayload["device"] = device.as<JsonObject>();
        autoconfPayload["availability_topic"] = _identifier + "/power/phase_1/instantaneous_current/status";
        autoconfPayload["state_topic"] = _identifier + "/power/phase_1/instantaneous_current";
        autoconfPayload["name"] = _identifier + "_phase_1_instantaneous_current";
        autoconfPayload["unit_of_measurement"] = "A";
        autoconfPayload["unique_id"] = "phase_1_instantaneous_current";
        autoconfPayload["icon"] = "mdi:flash";
        autoconfPayload["device_class"] = "current";
        autoconfPayload["state_class"] = "measurement";
        serializeJson(autoconfPayload, mqttPayload);
        _mqttPublisher.publish("homeassistant/sensor/" + _identifier + "/phase_1_instantaneous_current/config", &mqttPayload[0], false);
        autoconfPayload.clear();

        // instantaneous current phase 2
        autoconfPayload["device"] = device.as<JsonObject>();
        autoconfPayload["availability_topic"] = _identifier + "/power/phase_2/instantaneous_current/status";
        autoconfPayload["state_topic"] = _identifier + "/power/phase_2/instantaneous_current";
        autoconfPayload["name"] = _identifier + "_phase_2_instantaneous_current";
        autoconfPayload["unit_of_measurement"] = "A";
        autoconfPayload["unique_id"] = "phase_2_instantaneous_current";
        autoconfPayload["icon"] = "mdi:flash";
        autoconfPayload["device_class"] = "current";
        autoconfPayload["state_class"] = "measurement";
        serializeJson(autoconfPayload, mqttPayload);
        _mqttPublisher.publish("homeassistant/sensor/" + _identifier + "/phase_2_instantaneous_current/config", &mqttPayload[0], false);
        autoconfPayload.clear();

        // instantaneous current phase 3
        autoconfPayload["device"] = device.as<JsonObject>();
        autoconfPayload["availability_topic"] = _identifier + "/power/phase_3/instantaneous_current/status";
        autoconfPayload["state_topic"] = _identifier + "/power/phase_3/instantaneous_current";
        autoconfPayload["name"] = _identifier + "_phase_3_instantaneous_current";
        autoconfPayload["unit_of_measurement"] = "A";
        autoconfPayload["unique_id"] = "phase_3_instantaneous_current";
        autoconfPayload["icon"] = "mdi:flash";
        autoconfPayload["device_class"] = "current";
        autoconfPayload["state_class"] = "measurement";
        serializeJson(autoconfPayload, mqttPayload);
        _mqttPublisher.publish("homeassistant/sensor/" + _identifier + "/phase_3_instantaneous_current/config", &mqttPayload[0], false);
        autoconfPayload.clear();

        // instantaneous voltage phase 1
        autoconfPayload["device"] = device.as<JsonObject>();
        autoconfPayload["availability_topic"] = _identifier + "/power/phase_1/instantaneous_voltage/status";
        autoconfPayload["state_topic"] = _identifier + "/power/phase_1/instantaneous_voltage";
        autoconfPayload["name"] = _identifier + "_phase_1_instantaneous_voltage";
        autoconfPayload["unit_of_measurement"] = "V";
        autoconfPayload["unique_id"] = "phase_1_instantaneous_voltage";
        autoconfPayload["icon"] = "mdi:flash";
        autoconfPayload["device_class"] = "voltage";
        autoconfPayload["state_class"] = "measurement";
        serializeJson(autoconfPayload, mqttPayload);
        _mqttPublisher.publish("homeassistant/sensor/" + _identifier + "/phase_1_instantaneous_voltage/config", &mqttPayload[0], false);
        autoconfPayload.clear();

        // instantaneous voltage phase 2
        autoconfPayload["device"] = device.as<JsonObject>();
        autoconfPayload["availability_topic"] = _identifier + "/power/phase_2/instantaneous_voltage/status";
        autoconfPayload["state_topic"] = _identifier + "/power/phase_2/instantaneous_voltage";
        autoconfPayload["name"] = _identifier + "_phase_2_instantaneous_voltage";
        autoconfPayload["unit_of_measurement"] = "V";
        autoconfPayload["unique_id"] = "phase_2_instantaneous_voltage";
        autoconfPayload["icon"] = "mdi:flash";
        autoconfPayload["device_class"] = "voltage";
        autoconfPayload["state_class"] = "measurement";
        serializeJson(autoconfPayload, mqttPayload);
        _mqttPublisher.publish("homeassistant/sensor/" + _identifier + "/phase_2_instantaneous_voltage/config", &mqttPayload[0], false);
        autoconfPayload.clear();

        // instantaneous voltage phase 3
        autoconfPayload["device"] = device.as<JsonObject>();
        autoconfPayload["availability_topic"] = _identifier + "/power/phase_3/instantaneous_voltage/status";
        autoconfPayload["state_topic"] = _identifier + "/power/phase_3/instantaneous_voltage";
        autoconfPayload["name"] = _identifier + "_phase_3_instantaneous_voltage";
        autoconfPayload["unit_of_measurement"] = "V";
        autoconfPayload["unique_id"] = "phase_3_instantaneous_voltage";
        autoconfPayload["icon"] = "mdi:flash";
        autoconfPayload["device_class"] = "voltage";
        autoconfPayload["state_class"] = "measurement";
        serializeJson(autoconfPayload, mqttPayload);
        _mqttPublisher.publish("homeassistant/sensor/" + _identifier + "/phase_3_instantaneous_voltage/config", &mqttPayload[0], false);
        autoconfPayload.clear();
    }

    // Extra stuff here
    if (AUTOCONFIG_POWER_EXTENDED)
    {
        // short power outages
        autoconfPayload["device"] = device.as<JsonObject>();
        autoconfPayload["availability_topic"] = _identifier + "/power/short_power_outages/status";
        autoconfPayload["state_topic"] = _identifier + "/power/short_power_outages";
        autoconfPayload["name"] = _identifier + "_short_power_outages";
        autoconfPayload["unique_id"] = "short_power_outages";
        autoconfPayload["icon"] = "mdi:flash-off";
        serializeJson(autoconfPayload, mqttPayload);
        _mqttPublisher.publish("homeassistant/sensor/" + _identifier + "/short_power_outages/config", &mqttPayload[0], false);
        autoconfPayload.clear();

        // long power outages
        autoconfPayload["device"] = device.as<JsonObject>();
        autoconfPayload["availability_topic"] = _identifier + "/power/long_power_outages/status";
        autoconfPayload["state_topic"] = _identifier + "/power/long_power_outages";
        autoconfPayload["name"] = _identifier + "_long_power_outages";
        autoconfPayload["unique_id"] = "long_power_outages";
        autoconfPayload["icon"] = "mdi:flash-off";
        serializeJson(autoconfPayload, mqttPayload);
        _mqttPublisher.publish("homeassistant/sensor/" + _identifier + "/long_power_outages/config", &mqttPayload[0], false);
        autoconfPayload.clear();

        // instant current phase 1
        autoconfPayload["device"] = device.as<JsonObject>();
        autoconfPayload["availability_topic"] = _identifier + "/power/phase_1/current/status";
        autoconfPayload["state_topic"] = _identifier + "/power/phase_1/current";
        autoconfPayload["name"] = _identifier + "_phase_1_current";
        autoconfPayload["unit_of_measurement"] = "A";
        autoconfPayload["unique_id"] = "phase_1_current";
        autoconfPayload["icon"] = "mdi:flash";
        autoconfPayload["device_class"] = "current";
        autoconfPayload["state_class"] = "measurement";
        serializeJson(autoconfPayload, mqttPayload);
        _mqttPublisher.publish("homeassistant/sensor/" + _identifier + "/phase_1_current/config", &mqttPayload[0], false);
        autoconfPayload.clear();

        // instant current phase 2
        autoconfPayload["device"] = device.as<JsonObject>();
        autoconfPayload["availability_topic"] = _identifier + "/power/phase_2/current/status";
        autoconfPayload["state_topic"] = _identifier + "/power/phase_2/current";
        autoconfPayload["name"] = _identifier + "_phase_2_current";
        autoconfPayload["unit_of_measurement"] = "A";
        autoconfPayload["unique_id"] = "phase_2_current";
        autoconfPayload["icon"] = "mdi:flash";
        autoconfPayload["device_class"] = "current";
        autoconfPayload["state_class"] = "measurement";
        serializeJson(autoconfPayload, mqttPayload);
        _mqttPublisher.publish("homeassistant/sensor/" + _identifier + "/phase_2_current/config", &mqttPayload[0], false);
        autoconfPayload.clear();

        // instant current phase 3
        autoconfPayload["device"] = device.as<JsonObject>();
        autoconfPayload["availability_topic"] = _identifier + "/power/phase_3/current/status";
        autoconfPayload["state_topic"] = _identifier + "/power/phase_3/current";
        autoconfPayload["name"] = _identifier + "_phase_3_current";
        autoconfPayload["unit_of_measurement"] = "A";
        autoconfPayload["unique_id"] = "phase_3_current";
        autoconfPayload["icon"] = "mdi:flash";
        autoconfPayload["device_class"] = "current";
        autoconfPayload["state_class"] = "measurement";
        serializeJson(autoconfPayload, mqttPayload);
        _mqttPublisher.publish("homeassistant/sensor/" + _identifier + "/phase_3_current/config", &mqttPayload[0], false);
        autoconfPayload.clear();

        // instant consumption phase 1
        autoconfPayload["device"] = device.as<JsonObject>();
        autoconfPayload["availability_topic"] = _identifier + "/power/phase_1/consumption/status";
        autoconfPayload["state_topic"] = _identifier + "/power/phase_1/consumption";
        autoconfPayload["name"] = _identifier + "_phase_1_consumption";
        autoconfPayload["unit_of_measurement"] = "kW";
        autoconfPayload["unique_id"] = "phase_1_consumption";
        autoconfPayload["icon"] = "mdi:flash";
        autoconfPayload["device_class"] = "power";
        autoconfPayload["state_class"] = "measurement";
        serializeJson(autoconfPayload, mqttPayload);
        _mqttPublisher.publish("homeassistant/sensor/" + _identifier + "/phase_1_consumption/config", &mqttPayload[0], false);
        autoconfPayload.clear();

        // instant consumption phase 2
        autoconfPayload["device"] = device.as<JsonObject>();
        autoconfPayload["availability_topic"] = _identifier + "/power/phase_2/consumption/status";
        autoconfPayload["state_topic"] = _identifier + "/power/phase_2/consumption";
        autoconfPayload["name"] = _identifier + "_phase_2_consumption";
        autoconfPayload["unit_of_measurement"] = "kW";
        autoconfPayload["unique_id"] = "phase_2_consumption";
        autoconfPayload["icon"] = "mdi:flash";
        autoconfPayload["device_class"] = "power";
        autoconfPayload["state_class"] = "measurement";
        serializeJson(autoconfPayload, mqttPayload);
        _mqttPublisher.publish("homeassistant/sensor/" + _identifier + "/phase_2_consumption/config", &mqttPayload[0], false);
        autoconfPayload.clear();

        // instant consumption phase 3
        autoconfPayload["device"] = device.as<JsonObject>();
        autoconfPayload["availability_topic"] = _identifier + "/power/phase_3/consumption/status";
        autoconfPayload["state_topic"] = _identifier + "/power/phase_3/consumption";
        autoconfPayload["name"] = _identifier + "_phase_3_consumption";
        autoconfPayload["unit_of_measurement"] = "kW";
        autoconfPayload["unique_id"] = "phase_3_consumption";
        autoconfPayload["icon"] = "mdi:flash";
        autoconfPayload["device_class"] = "power";
        autoconfPayload["state_class"] = "measurement";
        serializeJson(autoconfPayload, mqttPayload);
        _mqttPublisher.publish("homeassistant/sensor/" + _identifier + "/phase_3_consumption/config", &mqttPayload[0], false);
        autoconfPayload.clear();

        // instant production phase 1
        autoconfPayload["device"] = device.as<JsonObject>();
        autoconfPayload["availability_topic"] = _identifier + "/power/phase_1/production/status";
        autoconfPayload["state_topic"] = _identifier + "/power/phase_1/production";
        autoconfPayload["name"] = _identifier + "_phase_1_production";
        autoconfPayload["unit_of_measurement"] = "kW";
        autoconfPayload["unique_id"] = "phase_1_production";
        autoconfPayload["icon"] = "mdi:flash";
        autoconfPayload["device_class"] = "power";
        autoconfPayload["state_class"] = "measurement";
        serializeJson(autoconfPayload, mqttPayload);
        _mqttPublisher.publish("homeassistant/sensor/" + _identifier + "/phase_1_production/config", &mqttPayload[0], false);
        autoconfPayload.clear();

        // instant production phase 2
        autoconfPayload["device"] = device.as<JsonObject>();
        autoconfPayload["availability_topic"] = _identifier + "/power/phase_2/production/status";
        autoconfPayload["state_topic"] = _identifier + "/power/phase_2/production";
        autoconfPayload["name"] = _identifier + "_phase_2_production";
        autoconfPayload["unit_of_measurement"] = "kW";
        autoconfPayload["unique_id"] = "phase_2_production";
        autoconfPayload["icon"] = "mdi:flash";
        autoconfPayload["device_class"] = "power";
        autoconfPayload["state_class"] = "measurement";
        serializeJson(autoconfPayload, mqttPayload);
        _mqttPublisher.publish("homeassistant/sensor/" + _identifier + "/phase_2_production/config", &mqttPayload[0], false);
        autoconfPayload.clear();

        // instant production phase 1
        autoconfPayload["device"] = device.as<JsonObject>();
        autoconfPayload["availability_topic"] = _identifier + "/power/phase_3/production/status";
        autoconfPayload["state_topic"] = _identifier + "/power/phase_3/production";
        autoconfPayload["name"] = _identifier + "_phase_3_production";
        autoconfPayload["unit_of_measurement"] = "kW";
        autoconfPayload["unique_id"] = "phase_3_production";
        autoconfPayload["icon"] = "mdi:flash";
        autoconfPayload["device_class"] = "power";
        autoconfPayload["state_class"] = "measurement";
        serializeJson(autoconfPayload, mqttPayload);
        _mqttPublisher.publish("homeassistant/sensor/" + _identifier + "/phase_3_production/config", &mqttPayload[0], false);
        autoconfPayload.clear();

        // short drops phase 1
        autoconfPayload["device"] = device.as<JsonObject>();
        autoconfPayload["availability_topic"] = _identifier + "/power/phase_1/drops/status";
        autoconfPayload["state_topic"] = _identifier + "/power/phase_1/drops";
        autoconfPayload["name"] = _identifier + "_phase_1_drops";
        autoconfPayload["unique_id"] = "phase_1_drops";
        autoconfPayload["icon"] = "mdi:chart-sankey";
        serializeJson(autoconfPayload, mqttPayload);
        _mqttPublisher.publish("homeassistant/sensor/" + _identifier + "/phase_1_drops/config", &mqttPayload[0], false);
        autoconfPayload.clear();

        // short drops phase 2
        autoconfPayload["device"] = device.as<JsonObject>();
        autoconfPayload["availability_topic"] = _identifier + "/power/phase_2/drops/status";
        autoconfPayload["state_topic"] = _identifier + "/power/phase_2/drops";
        autoconfPayload["name"] = _identifier + "_phase_2_drops";
        autoconfPayload["unique_id"] = "phase_2_drops";
        autoconfPayload["icon"] = "mdi:chart-sankey";
        serializeJson(autoconfPayload, mqttPayload);
        _mqttPublisher.publish("homeassistant/sensor/" + _identifier + "/phase_2_drops/config", &mqttPayload[0], false);
        autoconfPayload.clear();

        // short drops phase 3
        autoconfPayload["device"] = device.as<JsonObject>();
        autoconfPayload["availability_topic"] = _identifier + "/power/phase_3/drops/status";
        autoconfPayload["state_topic"] = _identifier + "/power/phase_3/drops";
        autoconfPayload["name"] = _identifier + "_phase_3_drops";
        autoconfPayload["unique_id"] = "phase_3_drops";
        autoconfPayload["icon"] = "mdi:chart-sankey";
        serializeJson(autoconfPayload, mqttPayload);
        _mqttPublisher.publish("homeassistant/sensor/" + _identifier + "/phase_3_drops/config", &mqttPayload[0], false);
        autoconfPayload.clear();

        // short peaks phase 1
        autoconfPayload["device"] = device.as<JsonObject>();
        autoconfPayload["availability_topic"] = _identifier + "/power/phase_1/drops/peaks";
        autoconfPayload["state_topic"] = _identifier + "/power/phase_1/peaks";
        autoconfPayload["name"] = _identifier + "_phase_1_peaks";
        autoconfPayload["unique_id"] = "phase_1_peaks";
        autoconfPayload["icon"] = "mdi:chart-bell-curve";
        serializeJson(autoconfPayload, mqttPayload);
        _mqttPublisher.publish("homeassistant/sensor/" + _identifier + "/phase_1_peaks/config", &mqttPayload[0], false);
        autoconfPayload.clear();

        // short peaks phase 2
        autoconfPayload["device"] = device.as<JsonObject>();
        autoconfPayload["availability_topic"] = _identifier + "/power/phase_2/drops/peaks";
        autoconfPayload["state_topic"] = _identifier + "/power/phase_2/peaks";
        autoconfPayload["name"] = _identifier + "_phase_2_peaks";
        autoconfPayload["unique_id"] = "phase_2_peaks";
        autoconfPayload["icon"] = "mdi:chart-bell-curve";
        serializeJson(autoconfPayload, mqttPayload);
        _mqttPublisher.publish("homeassistant/sensor/" + _identifier + "/phase_2_peaks/config", &mqttPayload[0], false);
        autoconfPayload.clear();

        // short peaks phase 3
        autoconfPayload["device"] = device.as<JsonObject>();
        autoconfPayload["availability_topic"] = _identifier + "/power/phase_3/drops/peaks";
        autoconfPayload["state_topic"] = _identifier + "/power/phase_3/peaks";
        autoconfPayload["name"] = _identifier + "_phase_3_peaks";
        autoconfPayload["unique_id"] = "phase_3_peaks";
        autoconfPayload["icon"] = "mdi:chart-bell-curve";
        serializeJson(autoconfPayload, mqttPayload);
        _mqttPublisher.publish("homeassistant/sensor/" + _identifier + "/phase_3_peaks/config", &mqttPayload[0], false);
        autoconfPayload.clear();
    }

    if (AUTOCONFIG_GAS)
    {
        // Gas
        autoconfPayload["device"] = device.as<JsonObject>();
        autoconfPayload["availability_topic"] = _identifier + "/gas/total/status";
        autoconfPayload["state_topic"] = _identifier + "/gas/total";
        autoconfPayload["name"] = _identifier + "_total_gas";
        autoconfPayload["unit_of_measurement"] = "m³";
        autoconfPayload["unique_id"] = "gas_total";
        autoconfPayload["icon"] = "mdi:counter";
        serializeJson(autoconfPayload, mqttPayload);
        _mqttPublisher.publish("homeassistant/sensor/" + _identifier + "/gas_total/config", &mqttPayload[0], false);
        autoconfPayload.clear();
    }
}
