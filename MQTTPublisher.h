#define MQTT_SOCKET_TIMEOUT 5
#pragma once
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <vector>
#include "PubSubClient.h"
#include "WiFiClient.h"

#define RECONNECT_TIMEOUT 15000

extern bool hasMQTT;
extern bool hasWIFI;

class MQTTPublisher
{
  private:
    bool debugMode;
    bool isStarted;

    uint32_t lastConnectionAttempt = 0; // last reconnect
    uint32_t lastUpdateMqtt; // last data send
   
    bool reconnect();
  public:
    MQTTPublisher(bool inDebugMode = false);
    ~MQTTPublisher();

    void start();
    void stop();

    void handle();
    bool publishOnMQTT(String prepend, String topic, String value);
};
