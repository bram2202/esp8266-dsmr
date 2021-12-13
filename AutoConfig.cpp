
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
    device["sw_version"] = "v1.3.1";

    // power_consumption
    autoconfPayload["device"] = device.as<JsonObject>();
    autoconfPayload["availability_topic"] = _identifier + "/power/consumption/status";
    autoconfPayload["state_topic"] = _identifier + "/power/consumption";
    autoconfPayload["last_reset_topic"] = _identifier + "/power/consumption/reset";
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
    autoconfPayload["last_reset_topic"] = _identifier + "/power/production/reset";
    autoconfPayload["name"] = _identifier + "_power_production";
    autoconfPayload["unit_of_measurement"] = "kW";
    autoconfPayload["unique_id"] = "power_production";
    autoconfPayload["icon"] = "mdi:flash";
    autoconfPayload["device_class"] = "power";
    autoconfPayload["state_class"] = "measurement";
    autoconfPayload["last_reset_value_template"] = "1970-01-01T00:00:00+00:00";
    serializeJson(autoconfPayload, mqttPayload);
    _mqttPublisher.publish("homeassistant/sensor/" + _identifier + "/power_production/config", &mqttPayload[0], false);
    autoconfPayload.clear();

    // total_consumption_tariff_1
    autoconfPayload["device"] = device.as<JsonObject>();
    autoconfPayload["availability_topic"] = _identifier + "/power/total_consumption_tariff_1/status";
    autoconfPayload["state_topic"] = _identifier + "/power/total_consumption_tariff_1";
    autoconfPayload["last_reset_topic"] = _identifier + "/power/total_consumption_tariff_1/reset";
    autoconfPayload["name"] = _identifier + "_total_consumption_tariff_1";
    autoconfPayload["unit_of_measurement"] = "kWh";
    autoconfPayload["unique_id"] = "total_consumption_tariff_1";
    autoconfPayload["icon"] = "mdi:counter";
    autoconfPayload["device_class"] = "energy";
    autoconfPayload["state_class"] = "measurement";
    autoconfPayload["last_reset_value_template"] = "1970-01-01T00:00:00+00:00";
    serializeJson(autoconfPayload, mqttPayload);
    _mqttPublisher.publish("homeassistant/sensor/" + _identifier + "/total_consumption_tariff_1/config", &mqttPayload[0], false);
    autoconfPayload.clear();

    // total_consumption_tariff_2
    autoconfPayload["device"] = device.as<JsonObject>();
    autoconfPayload["availability_topic"] = _identifier + "/power/total_consumption_tariff_2/status";
    autoconfPayload["state_topic"] = _identifier + "/power/total_consumption_tariff_2";
    autoconfPayload["last_reset_topic"] = _identifier + "/power/total_consumption_tariff_2/reset";
    autoconfPayload["name"] = _identifier + "_total_consumption_tariff_2";
    autoconfPayload["unit_of_measurement"] = "kWh";
    autoconfPayload["unique_id"] = "total_consumption_tariff_2";
    autoconfPayload["icon"] = "mdi:counter";
    autoconfPayload["device_class"] = "energy";
    autoconfPayload["state_class"] = "measurement";
    autoconfPayload["last_reset_value_template"] = "1970-01-01T00:00:00+00:00";
    serializeJson(autoconfPayload, mqttPayload);
    _mqttPublisher.publish("homeassistant/sensor/" + _identifier + "/total_consumption_tariff_2/config", &mqttPayload[0], false);
    autoconfPayload.clear();

    // total_production_tariff_1
    autoconfPayload["device"] = device.as<JsonObject>();
    autoconfPayload["availability_topic"] = _identifier + "/power/total_production_tariff_1/status";
    autoconfPayload["state_topic"] = _identifier + "/power/total_production_tariff_1";
    autoconfPayload["last_reset_topic"] = _identifier + "/power/total_production_tariff_1/reset";
    autoconfPayload["name"] = _identifier + "_total_production_tariff_1";
    autoconfPayload["unit_of_measurement"] = "kWh";
    autoconfPayload["unique_id"] = "total_production_tariff_1";
    autoconfPayload["icon"] = "mdi:counter";
    autoconfPayload["device_class"] = "energy";
    autoconfPayload["state_class"] = "measurement";
    autoconfPayload["last_reset_value_template"] = "1970-01-01T00:00:00+00:00";
    serializeJson(autoconfPayload, mqttPayload);
    _mqttPublisher.publish("homeassistant/sensor/" + _identifier + "/total_production_tariff_1/config", &mqttPayload[0], false);
    autoconfPayload.clear();

    // total_production_tariff_2
    autoconfPayload["device"] = device.as<JsonObject>();
    autoconfPayload["availability_topic"] = _identifier + "/power/total_production_tariff_2/status";
    autoconfPayload["state_topic"] = _identifier + "/power/total_production_tariff_2";
    autoconfPayload["last_reset_topic"] = _identifier + "/power/total_production_tariff_2/reset";
    autoconfPayload["name"] = _identifier + "_total_production_tariff_2";
    autoconfPayload["unit_of_measurement"] = "kWh";
    autoconfPayload["unique_id"] = "total_production_tariff_2";
    autoconfPayload["icon"] = "mdi:counter";
    autoconfPayload["device_class"] = "energy";
    autoconfPayload["state_class"] = "measurement";
    autoconfPayload["last_reset_value_template"] = "1970-01-01T00:00:00+00:00";
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

    // Extra stuff here
    if (AUTOCONFIG_POWER_EXTENDED)
    {
        // short power outages
        autoconfPayload["device"] = device.as<JsonObject>();
        autoconfPayload["availability_topic"] = _identifier + "/power/short_power_outages/status";
        autoconfPayload["state_topic"] = _identifier + "/power/short_power_outages";
        autoconfPayload["last_reset_topic"] = _identifier + "/power/short_power_outages/reset";
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
        autoconfPayload["last_reset_topic"] = _identifier + "/power/long_power_outages/reset";
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
        autoconfPayload["last_reset_topic"] = _identifier + "/power/phase_1/current/reset";
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
        autoconfPayload["last_reset_topic"] = _identifier + "/power/phase_2/current/reset";
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
        autoconfPayload["last_reset_topic"] = _identifier + "/power/phase_3/current/reset";
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
        autoconfPayload["last_reset_topic"] = _identifier + "/power/phase_1/consumption/reset";
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
        autoconfPayload["last_reset_topic"] = _identifier + "/power/phase_2/consumption/reset";
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
        autoconfPayload["last_reset_topic"] = _identifier + "/power/phase_3/consumption/reset";
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
        autoconfPayload["last_reset_topic"] = _identifier + "/power/phase_1/production/reset";
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
        autoconfPayload["last_reset_topic"] = _identifier + "/power/phase_2/production/reset";
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
        autoconfPayload["last_reset_topic"] = _identifier + "/power/phase_3/production/reset";
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
        autoconfPayload["last_reset_topic"] = _identifier + "/power/phase_1/drops/reset";
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
        autoconfPayload["last_reset_topic"] = _identifier + "/power/phase_2/drops/reset";
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
        autoconfPayload["last_reset_topic"] = _identifier + "/power/phase_3/drops/reset";
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
        autoconfPayload["last_reset_topic"] = _identifier + "/power/phase_1/peaks/reset";
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
        autoconfPayload["last_reset_topic"] = _identifier + "/power/phase_2/peaks/reset";
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
        autoconfPayload["last_reset_topic"] = _identifier + "/power/phase_3/peaks/reset";
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
        autoconfPayload["last_reset_topic"] = _identifier + "/gas/total/reset";
        autoconfPayload["name"] = _identifier + "_total_gas";
        autoconfPayload["unit_of_measurement"] = "m³";
        autoconfPayload["unique_id"] = "gas_total";
        autoconfPayload["icon"] = "mdi:counter";
        autoconfPayload["last_reset_value_template"] = "1970-01-01T00:00:00+00:00";
        serializeJson(autoconfPayload, mqttPayload);
        _mqttPublisher.publish("homeassistant/sensor/" + _identifier + "/total_gas/config", &mqttPayload[0], false);
        autoconfPayload.clear();
    }
}
