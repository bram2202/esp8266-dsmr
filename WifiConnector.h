#pragma once

extern bool hasWIFI;

class WifiConnector
{
  private:
    bool debugMode;
    bool tryingReconnect;

  public:
    WifiConnector(bool inDebugMode = false);
    void start();
    void handle();
    void reconnect();
};