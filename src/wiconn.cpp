#include <WiFiManager.h>
#include <WiFi.h>
#include "wiconn.h"
#include "config.h"
#include "prefs.h"
#include "mqtt.h"

WiFiManager wifiManager;

WiFiManagerParameter paramMqttServer("mqtt_server", "MQTT server", DEFAULT_MQTT_SERVER, 40);
WiFiManagerParameter paramMqttPort("mqtt_port", "MQTT port", DEFAULT_MQTT_PORT, 6);
WiFiManagerParameter paramMqttUser("mqtt_user", "MQTT user", DEFAULT_MQTT_USER, 40);
WiFiManagerParameter paramMqttPassword("mqtt_password", "MQTT password", DEFAULT_MQTT_PASSWORD, 40);
WiFiManagerParameter paramMqttTopic("mqtt_topic", "MQTT topic", DEFAULT_MQTT_TOPIC, 40);
WiFiManagerParameter paramElevatorSide("elevator_side", "Elevator side", DEFAULT_ELEVATOR_SIDE, 10);

int prevConfigButtonState = HIGH;

void setupWifi()
{
  WiFi.mode(WIFI_STA);
  WiFi.onEvent(onWifiEvent);

  // WiFiManager
  wifiManager.setDebugOutput(false);

  wifiManager.addParameter(&paramMqttServer);
  wifiManager.addParameter(&paramMqttPort);
  wifiManager.addParameter(&paramMqttUser);
  wifiManager.addParameter(&paramMqttPassword);
  wifiManager.addParameter(&paramMqttTopic);
  wifiManager.addParameter(&paramElevatorSide);

  wifiManager.setSaveParamsCallback(onSaveParams);
  wifiManager.setConfigResetCallback(onConfigReset);

  wifiManager.setConfigPortalTimeout(60 * 5); // 5 minutes
  wifiManager.setConfigPortalBlocking(false);

  wifiManager.autoConnect();
}

void loopWifi()
{
  wifiManager.process();
}

void checkConfigButton()
{
  int configButtonState = digitalRead(CONFIG_BUTTON_PIN);

  if (configButtonState == LOW && prevConfigButtonState == HIGH)
  {
    Serial.println("Entering config portal.");
    wifiManager.startConfigPortal();
    prevConfigButtonState = LOW;
  }
}

void onSaveParams()
{
  Serial.println("Saving preferences.");
  savePrefs();

  connectMqtt();
}

void onConfigReset()
{
  Serial.println("Resetting preferences.");
  resetPrefs();

  disconnectMqtt();
}

void onWifiEvent(WiFiEvent_t event)
{
  switch (event)
  {
  case SYSTEM_EVENT_STA_GOT_IP:
    Serial.print("Connected to ");
    Serial.println(WiFi.SSID());
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    connectMqtt();
    break;
  case SYSTEM_EVENT_STA_DISCONNECTED:
    Serial.println("Disconnected from WiFi access point");
    mqttClient.disconnect();
    break;
  }
}
