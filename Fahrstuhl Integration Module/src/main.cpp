#include <Arduino.h>
#include <Servo.h>

#define SERVO_PIN 12

#define LIGHT_SENSOR_PIN 14
Servo servo;

void setup()
{
  Serial.begin(115200);
  servo.attach(SERVO_PIN);
  pinMode(LIGHT_SENSOR_PIN, INPUT);
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

boolean notPressed;
boolean lightOn()
{
  if (analogRead(LIGHT_SENSOR_PIN) > 1000)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void pressWhenLightOff()
{
  if (lightOn())
  {
    notPressed = true;
  }
  else
  {
    if (notPressed)
    {
      pressButton();
      notPressed = false;
    }
  }
}

void loop()
{
}
