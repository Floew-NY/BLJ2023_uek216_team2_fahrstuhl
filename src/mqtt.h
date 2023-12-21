#pragma once

#include <AsyncMqttClient.h>

extern AsyncMqttClient mqttClient;

void setupMqtt();

void connectMqtt();

void disconnectMqtt();

void onMqttConnect(bool sessionPresent);

void onMqttDisconnect(AsyncMqttClientDisconnectReason reason);
