#pragma once

#include <AsyncMqttClient.h>

extern AsyncMqttClient mqttClient;

void connectMqtt();

void onMqttConnect(bool sessionPresent);

void onMqttDisconnect(AsyncMqttClientDisconnectReason reason);
