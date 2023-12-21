#include "integration.h"
#include <Arduino.h>
#include "config.h"
#include "mqtt.h"
#include "Servo.h"
#include "prefs.h"

boolean prevLightState = false;
boolean liftCalled = false;
Servo servo;

void integrationSetup()
{
  Serial.println("--- Elevator Integration Module ---");
  servo.attach(SERVO_PIN);
  pinMode(LIGHT_SENSOR_PIN, INPUT);

  subscribeMqtt("interface/call", callback);

  pressButton();
}

void integrationLoop()
{
  if (INTEGRATION_AUTOMATIC_MODE)
  {
    pressWhenLightOff(); // AUTOAMTILY GETS THE ELEVATOR
  }
  else
  {
    publishLiftState();
  }
}

void callback(char *topic, char *payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total)
{
  Serial.println("Received message: " + String(topic) + " - " + String(payload));
  if (strcmp(topic, "zuerich/elevator/interface/call") == 0)
  {
    pressButton();
    if (!lightOn())
    {
      publishMqtt("calling", "1");
    }
  }
}

boolean lightOn()
{
  return analogRead(LIGHT_SENSOR_PIN) > 1000;
}

void pressButton()
{
  servo.write(0);
  delay(20);
  servo.write(90);
  delay(100);
  servo.write(180);
  delay(20);
  servo.write(90);
}

void publishLiftState()
{
  boolean lightState = lightOn();
  if (lightState != prevLightState)
  {
    if (lightState)
    {
      Serial.println("Light on");
      publishMqtt(String(config_elevator_side) + "/presence", "1");
      publishMqtt("calling", "0");
    }
    else
    {
      Serial.println("Light off");
      publishMqtt(String(config_elevator_side) + "/presence", "0");
    }
    prevLightState = lightState;
  }
}

void pressWhenLightOff()
{
  boolean lightState = lightOn();
  if (lightState != prevLightState)
  {
    if (!lightState)
    {
      pressButton();
    }
  }
  prevLightState = lightState;
}