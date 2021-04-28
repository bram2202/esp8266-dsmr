#pragma once
#include "Logger.h"

extern bool hasWIFI;

class WifiConnector
{
  private:
    Logger logger;
    bool tryingReconnect;

  public:
    WifiConnector();
    void start();
    void handle();
    void reconnect();
};
