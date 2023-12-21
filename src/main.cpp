#include <Arduino.h>
#include <Preferences.h>
#include "config.h"
#include "mqtt.h"
#include "prefs.h"
#include "wiconn.h"

#ifdef INTEGRATION
#include "integration.h"
#else
#include "interface.h"
#endif

void setup()
{
  Serial.begin(SERIAL_BAUD_RATE);

  setupPrefs();

  setupMqtt();

  setupWifi();

  // Main setup
#ifdef INTEGRATION
  integrationSetup();
#else
  interfaceSetup();
#endif
}

void loop()
{
  checkConfigButton();

  loopWifi();

#ifdef INTEGRATION
  integrationLoop();
#else
  interfaceLoop();
#endif
}
