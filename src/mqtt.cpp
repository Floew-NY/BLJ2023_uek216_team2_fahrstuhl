#include <AsyncMqttClient.h>
#include "mqtt.h"
#include "prefs.h"

AsyncMqttClient mqttClient;

void connectMqtt()
{
  mqttClient.disconnect();
  mqttClient.setServer(config_mqtt_server, atoi(config_mqtt_port));
  mqttClient.setCredentials(config_mqtt_user, config_mqtt_password);
  Serial.println("Connecting to MQTT...");
  mqttClient.connect();
}

void onMqttConnect(bool sessionPresent)
{
  Serial.println("Connected to MQTT.");
}

void onMqttDisconnect(AsyncMqttClientDisconnectReason reason)
{
  Serial.println("Disconnected from MQTT.");
}
