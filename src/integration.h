#pragma once

#include <Arduino.h>
#include "mqtt.h"

void integrationSetup();

void integrationLoop();

void pressButton();

boolean lightOn();

void pressWhenLightOff();

void callback(char *topic, char *payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total);

void publishLiftState();