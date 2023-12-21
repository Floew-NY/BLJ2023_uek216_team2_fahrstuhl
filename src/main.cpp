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

/*
 * Preferences
 */

/*
 * MQTT
 */

/*
 * WiFi
 */

/*
 * Main
 */
void setup()
{
  Serial.begin(SERIAL_BAUD_RATE);

  // Preferences
  preferences.begin("config", false);
  loadPrefs();

  // MQTT
  mqttClient.onConnect(onMqttConnect);
  mqttClient.onDisconnect(onMqttDisconnect);

  // WiFi
  WiFi.mode(WIFI_STA);
  WiFi.onEvent(onWifiEvent);

  // WiFiManager
  wifiManager.setDebugOutput(false);

  wifiManager.addParameter(&paramMqttServer);
  wifiManager.addParameter(&paramMqttPort);
  wifiManager.addParameter(&paramMqttUser);
  wifiManager.addParameter(&paramMqttPassword);
  wifiManager.addParameter(&paramMqttTopic);
  wifiManager.setSaveParamsCallback(onSaveParams);

  wifiManager.setConfigPortalTimeout(60 * 5); // 5 minutes
  wifiManager.setConfigPortalBlocking(false);

  wifiManager.autoConnect();

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

  wifiManager.process();

#ifdef INTEGRATION
  integrationLoop();
#else
  interfaceLoop();
#endif
}

/*
 * Preferences
 */

/*
 * MQTT
 */

/*
 * WiFi
 */
