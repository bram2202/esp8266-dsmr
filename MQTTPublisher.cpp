#include "MQTTPublisher.h"
#include "Settings.h"

WiFiClient espClient;
PubSubClient client(espClient);

MQTTPublisher::MQTTPublisher(String clientId)
{
  randomSeed(micros());
  _clientId = clientId;
  logger = Logger("MQTTPublisher");
  logger.debug("ClientId:" + _clientId);
}

MQTTPublisher::~MQTTPublisher() 
{
  client.publish(getTopic("status").c_str(), "offline");
  client.disconnect();
}

String MQTTPublisher::getTopic(String name)
{
  if (USE_CLIENT_ID)
  {
    return String(MQTT_PREFIX) + '/' + _clientId + '/' + name;
  }
  else
  {
    return String(MQTT_PREFIX) + '/' + name;
  }
}

bool MQTTPublisher::reconnect()
{
  lastConnectionAttempt = millis();

  logger.debug("Attempt connection to server: " + String(MQTT_HOST_NAME));

  // Attempt to connect
  bool clientConnected;
  if (String(MQTT_USER_NAME).length())
  {
    logger.info("Connecting with credientials");
    clientConnected = client.connect(_clientId.c_str(), MQTT_USER_NAME, MQTT_PASSWORD);
  }
  else
  {
    logger.info("Connecting without credentials");
    clientConnected = client.connect(_clientId.c_str());
  }

  if (clientConnected)
  {
    logger.debug("connected");

    hasMQTT = true;

    // Once connected, publish an announcement...
    client.publish(getTopic("status").c_str(), "online");

    return true;
  }
  else
  {
    logger.warn("failed, rc=" + client.state());
  }

  return false;
}

void MQTTPublisher::start()
{
  if (String(MQTT_HOST_NAME).length() == 0 || MQTT_PORT == 0)
  {
    logger.warn("disabled. No hostname or port set.");
    return; //not configured
  }

  logger.debug("enabled. Connecting.");

  client.setServer(MQTT_HOST_NAME, MQTT_PORT);
  reconnect();
  isStarted = true;
}

void MQTTPublisher::stop()
{
  isStarted = false;
}

void MQTTPublisher::handle()
{
  if (!isStarted)
    return;

  if (!client.connected() && millis() - lastConnectionAttempt > RECONNECT_TIMEOUT)
  {
    hasMQTT = false;
    if (!reconnect())
      return;
  }
}

bool MQTTPublisher::publishOnMQTT(String topicSuffix, String msg)
{
  String topic = getTopic(topicSuffix);
  logger.debug("Publish to '" + topic + "':" + msg);
  auto retVal = client.publish(topic.c_str(), msg.c_str());
  yield();
  return retVal;
}
