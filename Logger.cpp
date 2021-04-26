#include "Logger.h"
#include "Settings.h"

enum LEVEL
{
  DEBUG = 1,
  INFO = 2,
  WARN = 3
};

// Create Wifi Connector
Logger::Logger(String name)
{
  _name = name;
}

void Logger::debug(String msg)
{
  if (LOG_LEVEL <= DEBUG)
  {
    Serial.println("DEBUG - " + _name + ":" + msg);
  }
}

void Logger::info(String msg)
{
  if (LOG_LEVEL <= INFO)
  {
    Serial.println("INFO - " + _name + ":" + msg);
  }
}

void Logger::warn(String msg)
{
  if (LOG_LEVEL <= WARN)
  {
    Serial.println("WARN - " + _name + ":" + msg);
  }
}
