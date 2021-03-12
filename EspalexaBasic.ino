#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <Espalexa.h>
#include "config.h"

boolean connectWifi();

void firstLightChanged(uint8_t brightness);

const char *ssid = "";
const char *password = "!";

boolean wifiConnected = false;
Espalexa espalexa;

//http://192.168.1.23/espalexa
void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.begin(SERIALBAUDS);
  while (!Serial) continue;
  wifiConnected = connectWifi();

  if (wifiConnected)
  {
    espalexa.addDevice(DEVICE_NAME, firstLightChanged); //simplest definition, default state off
    espalexa.begin();
  }
  else
  {
    while (1)
    {
      Serial.println("Cannot connect to WiFi. Please check data and reset the ESP.");
      delay(2500);
    }
  }
}

void loop()
{
  espalexa.loop();
  delay(1);
}

//our callback functions
void firstLightChanged(uint8_t brightness)
{
  if (brightness > 0)
    digitalWrite(LED_BUILTIN, LOW);

  if (brightness == 0)
    digitalWrite(LED_BUILTIN, HIGH);

  Serial.print("Brightness: ");
  Serial.println(brightness);
}

// connect to wifi – returns true if successful or false if not
boolean connectWifi()
{
  boolean state = true;
  int i = 0;

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    if (i > 20)
    {
      state = false;
      break;
    }
    i++;
  }
  Serial.println("");
  if (state)
  {
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else
  {
    Serial.println("Connection failed.");
  }
  return state;
}
