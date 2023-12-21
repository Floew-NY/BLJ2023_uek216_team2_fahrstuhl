#include <AsyncMqttClient.h>
#include <vector>
#include "mqtt.h"
#include "prefs.h"

AsyncMqttClient mqttClient;

std::vector<MQTTSubscription> mqttSubscriptions;

String getFullTopic(String topic)
{
  String configTopic = String(config_mqtt_topic);
  if (configTopic.endsWith("/"))
  {
    configTopic.remove(configTopic.length() - 1);
  }
  return configTopic + "/" + topic;
}

void setupMqtt()
{
  mqttClient.onConnect(onMqttConnect);
  mqttClient.onDisconnect(onMqttDisconnect);
  mqttClient.onMessage(onMqttMessage);
}

void subscribeMqtt(String topic, AsyncMqttClientInternals::OnMessageUserCallback callback, bool exact, uint8_t qos)
{
  MQTTSubscription subscription;
  subscription.topic = topic;
  subscription.callback = callback;
  subscription.qos = qos;
  subscription.exact = exact;
  mqttSubscriptions.push_back(subscription);
  if (mqttClient.connected())
  {
    mqttClient.subscribe(getFullTopic(topic).c_str(), qos);
  }
}

void publishMqtt(String topic, String payload, bool retain, uint8_t qos)
{
  mqttClient.publish(getFullTopic(topic).c_str(), qos, retain, payload.c_str());
}

void connectMqtt()
{
  mqttClient.disconnect();
  mqttClient.setServer(config_mqtt_server, atoi(config_mqtt_port));
  mqttClient.setCredentials(config_mqtt_user, config_mqtt_password);
  Serial.println("Connecting to MQTT...");
  mqttClient.connect();
}

void disconnectMqtt()
{
  mqttClient.disconnect();
}

void onMqttMessage(char *topic, char *payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total)
{
  String topicString = String(topic);
  for (size_t i = 0; i < mqttSubscriptions.size(); i++)
  {
    MQTTSubscription subscription = mqttSubscriptions[i];
    if ((subscription.exact && getFullTopic(subscription.topic) == topicString) || (!subscription.exact && topicString.startsWith(getFullTopic(subscription.topic))))
    {
      subscription.callback(topic, payload, properties, len, index, total);
    }
  }
}

void onMqttConnect(bool sessionPresent)
{
  Serial.println("Connected to MQTT.");
  for (size_t i = 0; i < mqttSubscriptions.size(); i++)
  {
    MQTTSubscription subscription = mqttSubscriptions[i];
    mqttClient.subscribe(getFullTopic(subscription.topic).c_str(), subscription.qos);
  }
}

void onMqttDisconnect(AsyncMqttClientDisconnectReason reason)
{
  Serial.println("Disconnected from MQTT.");
}
