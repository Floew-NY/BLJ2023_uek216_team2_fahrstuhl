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

  wifiman_setup();

#ifdef INTEGRATION
  integration_setup();
#else
  interface_setup();
#endif
}

void loop()
{
  wifiman_loop();

#ifdef INTEGRATION
  integration_loop();
#else
  interface_loop();
#endif
}
