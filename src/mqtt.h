#pragma once

#include <Arduino.h>
#include <AsyncMqttClient.h>
#include <vector>

extern AsyncMqttClient mqttClient;

typedef struct
{
  String topic;
  AsyncMqttClientInternals::OnMessageUserCallback callback;
  uint8_t qos;
  bool exact;
} MQTTSubscription;

extern std::vector<MQTTSubscription> mqttSubscriptions;

String getFullTopic(String topic);

void setupMqtt();

void subscribeMqtt(String topic, AsyncMqttClientInternals::OnMessageUserCallback callback, bool exact = false, uint8_t qos = 0);

void connectMqtt();

void disconnectMqtt();

void onMqttMessage(char *topic, char *payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total);

void onMqttConnect(bool sessionPresent);

void onMqttDisconnect(AsyncMqttClientDisconnectReason reason);
