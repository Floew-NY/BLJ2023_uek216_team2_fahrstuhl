#include "interface.h"
#include <Arduino.h>
#include "config.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <mqtt.h>

#define WHITE SSD1306_WHITE
#define BLACK SSD1306_BLACK

Adafruit_SSD1306 display(128, 32, &Wire, -1);

int prevCallButtonState = LOW;

void displayDoorOpen()
{
  display.fillRect(4, 5, 21, 28, WHITE);
  display.fillRect(7, 7, 15, 26, BLACK);
}

void displayDoorClosed()
{
  display.fillRect(4, 5, 21, 28, WHITE);
  display.fillRect(6, 6, 17, 27, BLACK);
  display.fillRect(7, 7, 7, 26, WHITE);
  display.fillRect(15, 7, 7, 26, WHITE);
}

void interfaceSetup()
{
  Serial.println("--- User Interface Module ---");

  pinMode(CALL_BUTTON_PIN, INPUT);
  pinMode(LIGHT_RED_PIN, OUTPUT);
  pinMode(LIGHT_GREEN_PIN, OUTPUT);
  pinMode(LIGHT_BLUE_PIN, OUTPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
}

void interfaceLoop()
{
  digitalWrite(LIGHT_RED_PIN, HIGH);
  display.clearDisplay();
  display.setCursor(0, 0);
  int callButtonState = digitalRead(CALL_BUTTON_PIN);
  displayDoorClosed();
  display.display();
  if (callButtonState == HIGH)
  {
    if (prevCallButtonState == LOW)
    {
      publishMqtt("interface/call");
      digitalWrite(LIGHT_RED_PIN, HIGH);
      digitalWrite(LIGHT_GREEN_PIN, HIGH);
      displayDoorOpen();
      display.display();
    }
  }
  prevCallButtonState = callButtonState;
}
