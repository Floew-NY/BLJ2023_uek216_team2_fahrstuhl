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

bool leftPresence = false;
bool prevLeftPresence = false;

bool rightPresence = false;
bool prevRightPresence = false;

bool calling = false;
bool prevCalling = false;

void renderDoor(bool isOpen, int xOffset)
{
  if (isOpen)
  {
    display.fillRect(4 + xOffset, 5, 21, 28, WHITE);
    display.fillRect(7 + xOffset, 7, 15, 26, BLACK);
  }
  else
  {
    display.fillRect(4 + xOffset, 5, 21, 28, WHITE);
    display.fillRect(6 + xOffset, 6, 17, 27, BLACK);
    display.fillRect(7 + xOffset, 7, 7, 26, WHITE);
    display.fillRect(15 + xOffset, 7, 7, 26, WHITE);
  }
}

void handleLeftPresence(char *topic, char *payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total)
{
  leftPresence = String(payload).charAt(0) == '1';
}

void handleRightPresence(char *topic, char *payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total)
{
  Serial.println(payload);
  rightPresence = String(payload).charAt(0) == '1';
}

void handleCalling(char *topic, char *payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total)
{
  calling = String(payload).charAt(0) == '1';
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
  display.display();

  subscribeMqtt("left/presence", handleLeftPresence, false, 2);
  subscribeMqtt("right/presence", handleRightPresence, false, 2);
  subscribeMqtt("calling", handleCalling, false, 2);
}

void interfaceLoop()
{
  int callButtonState = digitalRead(CALL_BUTTON_PIN);

  if (prevLeftPresence != leftPresence || prevRightPresence != rightPresence || prevCalling != calling)
  {
    display.clearDisplay();

    prevLeftPresence = leftPresence;
    prevRightPresence = rightPresence;
    prevCalling = calling;

    String text;

    if (calling)
    {
      text = "Coming";
      digitalWrite(LIGHT_RED_PIN, HIGH);
      digitalWrite(LIGHT_GREEN_PIN, HIGH);
    }
    else if (leftPresence || rightPresence)
    {
      text = "Here";

      digitalWrite(LIGHT_RED_PIN, LOW);
      digitalWrite(LIGHT_GREEN_PIN, HIGH);
    }
    else
    {
      text = "Gone";

      digitalWrite(LIGHT_RED_PIN, HIGH);
      digitalWrite(LIGHT_GREEN_PIN, LOW);
    }
    display.setCursor(32, 15);
    display.print(text);

    renderDoor(leftPresence, 0);
    renderDoor(rightPresence, 101);

    display.display();
  }

  if (callButtonState == HIGH && prevCallButtonState == LOW)
  {
    publishMqtt("call");
  }
  prevCallButtonState = callButtonState;
}
