#pragma once

#include <Preferences.h>

extern Preferences preferences;

// Preference defaults
#define DEFAULT_MQTT_SERVER ""
#define DEFAULT_MQTT_PORT "1883"
#define DEFAULT_MQTT_USER ""
#define DEFAULT_MQTT_PASSWORD ""
#define DEFAULT_MQTT_TOPIC "zuerich/elevator/"

// Preferences
extern char config_mqtt_server[40];
extern char config_mqtt_port[6];
extern char config_mqtt_user[40];
extern char config_mqtt_password[40];
extern char config_mqtt_topic[40];

void setupPrefs();

void loadPrefs();

void savePrefs();

void resetPrefs();
