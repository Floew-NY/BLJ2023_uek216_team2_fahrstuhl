#include <Arduino.h>
#include "wifiman.h"
#include "config.h"

#ifdef INTEGRATION
#include "integration.h"
#else
#include "interface.h"
#endif

void setup()
{
  Serial.begin(SERIAL_BAUD_RATE);

  wifimanSetup();

#ifdef INTEGRATION
  integrationSetup();
#else
  interfaceSetup();
#endif
}

void loop()
{
  wifimanLoop();

#ifdef INTEGRATION
  integrationLoop();
#else
  interfaceLoop();
#endif
}
