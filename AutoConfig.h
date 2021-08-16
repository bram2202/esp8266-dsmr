#pragma once
#include <ArduinoJson.h>
#include "MQTTPublisher.h"
#include "Settings.h"
#include "Logger.h"

class AutoConfig
{
private:
  Logger logger;
  MQTTPublisher _mqttPublisher;
  String _identifier;
  
public:
  AutoConfig(MQTTPublisher& mqttPublisher, String identifier);
  AutoConfig();

  void SendConfig();
};