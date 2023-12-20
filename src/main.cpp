#include <Arduino.h>
#include "config.h"

// #define INTEGRATION

#ifdef INTEGRATION
#include "integration.h"
#else
#include "interface.h"
#endif

void setup()
{
  Serial.begin(SERIAL_BAUD_RATE);

#ifdef INTEGRATION
  integration_setup();
#else
  interface_setup();
#endif
}

void loop()
{
#ifdef INTEGRATION
  integration_loop();
#else
  interface_loop();
#endif
}
