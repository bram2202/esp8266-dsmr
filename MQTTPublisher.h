#define MQTT_SOCKET_TIMEOUT 5
#pragma once
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <vector>
#include "PubSubClient.h"
#include "WiFiClient.h"
#include "Logger.h"

#define RECONNECT_TIMEOUT 15000

extern bool hasMQTT;
extern bool hasWIFI;

class MQTTPublisher
{
  private:
    Logger logger;
    bool _debugMode;
    String _clientId;
    bool isStarted;

    uint32_t lastConnectionAttempt = 0; // last reconnect
    uint32_t lastUpdateMqtt; // last data send
   
    bool reconnect();
    String getTopic(String name);
  public:
    MQTTPublisher(String clientId = String(ESP.getChipId(), HEX));
    ~MQTTPublisher();

    void start();
    void stop();

    void handle();
    bool publishOnMQTT(String topic, String msg);
};
