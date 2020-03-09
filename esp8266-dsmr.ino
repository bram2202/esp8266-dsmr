#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPClient.h>
#include <WiFiUdp.h>
#include "MQTTPublisher.h"
#include "WifiConnector.h"
#include "ESP8266mDNS.h"
#include "Settings.h"

MQTTPublisher mqqtPublisher(DEBUGE_MODE);
WifiConnector wifiConnector(DEBUGE_MODE);
WiFiUDP ntpUDP;
String incomingString = "";
bool hasMQTT = false;
bool hasWIFI = false;

void setup() {

  // Start serial ESP8266 RX port (pin 3)
  Serial.begin(115200);
  pinMode(3, FUNCTION_0);

  if (DEBUGE_MODE) {
    Serial.println("Booting");
  }

  // Setup Wifi
  wifiConnector.start();

  // Setup MQTT
  mqqtPublisher.start();
}

void loop() {
  
  wifiConnector.handle();
  yield();
  mqqtPublisher.handle();
  yield();

  // If serial received, read until newline
  if (Serial.available() > 0) {
    incomingString = Serial.readStringUntil('\n');
    handelString(incomingString);
  }
}

// Regex are not supported, so use indexOf and substring
void handelString(String incomingString) {

  // DSMR version
  int found1 = incomingString.indexOf("1-3:0.2.8");
  if (found1 > -1) {
    String value1 = incomingString.substring(10, 12);
    if (DEBUGE_MODE)
      Serial.println("0.2.8= " + value1);
    mqqtPublisher.publishOnMQTT(MQTT_TOPIC, "/version", value1);
  }

  // Power consuption
  int found2 = incomingString.indexOf("1-0:1.7.0");
  if (found2 > -1) {
    String value2 = String(incomingString.substring(10, 16).toFloat(), 3);
    if (DEBUGE_MODE)
      Serial.println("1.7.0= " + value2);
    mqqtPublisher.publishOnMQTT(MQTT_TOPIC, "/power_consuption", value2);
  }

  // Power production
  int found3 = incomingString.indexOf("1-0:2.7.0");
  if (found3 > -1) {
    String value3 = String(incomingString.substring(10, 16).toFloat(), 3);
    if (DEBUGE_MODE)
      Serial.println("2.7.0= " + value3);
    mqqtPublisher.publishOnMQTT(MQTT_TOPIC, "/power_production", value3);
  }

  // Total consuption low
  int found4 = incomingString.indexOf("1-0:1.8.1");
  if (found4 > -1) {
    String value4 = String(incomingString.substring(10, 20).toFloat(), 3);
    if (DEBUGE_MODE)
      Serial.println("1.8.1= " + value4);
    mqqtPublisher.publishOnMQTT(MQTT_TOPIC, "/total_consuption_low", value4);
  }

  // Total consuption high
  int found5 = incomingString.indexOf("1-0:1.8.2");
  if (found5 > -1) {
    String value5 = String(incomingString.substring(10, 20).toFloat(), 3);
    if (DEBUGE_MODE)
      Serial.println("1.8.2= " + value5);
    mqqtPublisher.publishOnMQTT(MQTT_TOPIC, "/total_consuption_high", value5);
  }

  // Total production low
  int found6 = incomingString.indexOf("1-0:2.8.1");
  if (found6 > -1) {
    String value6 = String(incomingString.substring(10, 20).toFloat(), 3);
    if (DEBUGE_MODE)
      Serial.println("2.8.1= " + value6);
    mqqtPublisher.publishOnMQTT(MQTT_TOPIC, "/total_production_low", value6);
  }

  // Total production high
  int found7 = incomingString.indexOf("1-0:2.8.2");
  if (found7 > -1) {
    String value7 = String(incomingString.substring(10, 20).toFloat(), 3);
    if (DEBUGE_MODE)
      Serial.println("2.8.2= " + value7);
    mqqtPublisher.publishOnMQTT(MQTT_TOPIC, "/total_production_high", value7);
  }

  // Total gas
  int found8 = incomingString.indexOf("0-1:24.2.1");
  if (found8 > -1) {
    String value8 = String(incomingString.substring(26, 35).toFloat(), 3);
    if (DEBUGE_MODE)
      Serial.println("24.2.1= " + value8);
    mqqtPublisher.publishOnMQTT(MQTT_TOPIC, "/total_gas", value8);
  }

  // Power tariff (1 low, 2 high)
  int found9 = incomingString.indexOf("0-0:96.14.0");
  if (found9 > -1) {
    String value9 = String(incomingString.substring(12, 16).toInt());
    if (DEBUGE_MODE)
      Serial.println("96.14.0= " + value9);
    mqqtPublisher.publishOnMQTT(MQTT_TOPIC, "/power_tariff", value9);
  }

}
