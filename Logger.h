#pragma once
#include <Arduino.h>

class Logger
{
private:
  String _name;

public:
  Logger(String name = "Logger");
  void info(String msg);
  void debug(String msg);
  void warn(String msg);
};
