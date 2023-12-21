#pragma once

#include <WiFiManager.h>
#include <WiFi.h>
#include "prefs.h"

extern WiFiManager wifiManager;

// WiFiManager parameters
extern WiFiManagerParameter paramMqttServer;
extern WiFiManagerParameter paramMqttPort;
extern WiFiManagerParameter paramMqttUser;
extern WiFiManagerParameter paramMqttPassword;
extern WiFiManagerParameter paramMqttTopic;

extern int prevButtonState;

void setupWifi();

void loopWifi();

void checkConfigButton();

void onSaveParams();

void onWifiEvent(WiFiEvent_t event);