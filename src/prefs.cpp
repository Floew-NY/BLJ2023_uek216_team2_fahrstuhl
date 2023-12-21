#include <Preferences.h>
#include "prefs.h"
#include "wiconn.h"

Preferences preferences;

char config_mqtt_server[40] = DEFAULT_MQTT_SERVER;
char config_mqtt_port[6] = DEFAULT_MQTT_PORT;
char config_mqtt_user[40] = DEFAULT_MQTT_USER;
char config_mqtt_password[40] = DEFAULT_MQTT_PASSWORD;
char config_mqtt_topic[40] = DEFAULT_MQTT_TOPIC;

void setupPrefs()
{
  preferences.begin("config", false);
  loadPrefs();
}

void loadPrefs()
{
  strcpy(config_mqtt_server, preferences.getString("mqtt_server", config_mqtt_server).c_str());
  strcpy(config_mqtt_port, preferences.getString("mqtt_port", config_mqtt_port).c_str());
  strcpy(config_mqtt_user, preferences.getString("mqtt_user", config_mqtt_user).c_str());
  strcpy(config_mqtt_password, preferences.getString("mqtt_password", config_mqtt_password).c_str());
  strcpy(config_mqtt_topic, preferences.getString("mqtt_topic", config_mqtt_topic).c_str());

  paramMqttServer.setValue(config_mqtt_server, 40);
  paramMqttPort.setValue(config_mqtt_port, 6);
  paramMqttUser.setValue(config_mqtt_user, 40);
  paramMqttPassword.setValue(config_mqtt_password, 40);
  paramMqttTopic.setValue(config_mqtt_topic, 40);
}

void savePrefs()
{
  preferences.putString("mqtt_server", paramMqttServer.getValue());
  preferences.putString("mqtt_port", paramMqttPort.getValue());
  preferences.putString("mqtt_user", paramMqttUser.getValue());
  preferences.putString("mqtt_password", paramMqttPassword.getValue());
  preferences.putString("mqtt_topic", paramMqttTopic.getValue());

  loadPrefs();
}

void resetPrefs()
{
  preferences.clear();

  strcpy(config_mqtt_server, DEFAULT_MQTT_SERVER);
  strcpy(config_mqtt_port, DEFAULT_MQTT_PORT);
  strcpy(config_mqtt_user, DEFAULT_MQTT_USER);
  strcpy(config_mqtt_password, DEFAULT_MQTT_PASSWORD);
  strcpy(config_mqtt_topic, DEFAULT_MQTT_TOPIC);

  savePrefs();
}
