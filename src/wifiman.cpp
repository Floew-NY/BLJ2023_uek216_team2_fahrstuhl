#include "wifiman.h"
#include <Arduino.h>
#include "config.h"
#include <WiFiManager.h>

WiFiManager wifiManager;

long prevButtonState = HIGH;

void wifiman_setup()
{
  wifiManager.setConfigPortalTimeout(60 * 5); // 5 minutes
  wifiManager.setConfigPortalBlocking(false);

  wifiManager.autoConnect();

  Serial.println("Connected to WiFi.");
}

void wifiman_loop()
{
  int buttonState = digitalRead(CONFIG_BUTTON_PIN);

  if (buttonState == LOW && prevButtonState == HIGH)
  {
    Serial.println("Entering config portal.");
    wifiManager.startConfigPortal();
    prevButtonState = LOW;
  }

  wifiManager.process();
}
