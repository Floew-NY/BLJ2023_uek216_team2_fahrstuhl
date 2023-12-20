#pragma once

#include <Arduino.h>
#include "config.h"
#include <WiFiManager.h>

extern WiFiManager wifiManager;

void wifiman_setup();

void wifiman_loop();

#pragma endregion