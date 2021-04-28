#include "WifiConnector.h"
#include "Settings.h"
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPClient.h>
#include <WiFiUdp.h>
#include "ESP8266mDNS.h"

// Create Wifi Connector
WifiConnector::WifiConnector()
{
  logger = Logger("WifiConnector");
  tryingReconnect = false;
}

// Set params and try to connect
void WifiConnector::start()
{

  logger.info("Start");

  // Setup Wifi
  WiFi.mode(WIFI_STA);
  WiFi.hostname(WIFI_HOSTNAME);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  // This funtion is called from main setup function,
  // Wait until unit has wifi before continuing
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    logger.debug(".");
  }

  // Set wifi bool
  hasWIFI = true;

  logger.info("Connected!");
  logger.debug("IP: " + WiFi.localIP());
}

// If wifi connection is lost, try to reconnect
void WifiConnector::reconnect()
{

  logger.debug("Try to reconnect!");

  // First hit, try to reconnect.
  if (!tryingReconnect)
  {
    WiFi.reconnect();
    tryingReconnect = true;
  }
}

// handle function called from main loop
void WifiConnector::handle()
{

  // Check if WIfi is Connected
  if (!WiFi.isConnected() && !tryingReconnect)
  {

    logger.info("Disconnected!");

    // Set bool false and try to reconnect
    hasWIFI = false;
    reconnect();
  }
  else if (WiFi.isConnected() && !hasWIFI)
  { // Wifi is Reconnected

    logger.info("Reconnected!");

    hasWIFI = true;
    tryingReconnect = false;
  }
}
