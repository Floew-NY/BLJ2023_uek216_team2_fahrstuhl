#pragma once

#include <Arduino.h>
#include "config.h"
#include <WiFiManager.h>

extern WiFiManager wifiManager;

void wifimanSetup();

void wifimanLoop();

#pragma endregion