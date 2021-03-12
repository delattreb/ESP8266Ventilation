#include <ESP8266WiFi.h>
#include <WiFiManager.h>
#include <EEPROM.h>
#include <Espalexa.h>
#include "config.h"

WiFiClient wifiClient;
Espalexa espalexa;

void firstLightChanged(uint8_t brightness);

//Setup
void setup()
{
#ifdef SERIALLOG
  Serial.begin(SERIALBAUDS);
  while (!Serial)
    continue;
#endif
#ifdef INFO
  delay(5000);
  Serial.print("Core version: ");
  Serial.println(ESP.getCoreVersion());
  Serial.print("Sdk version: ");
  Serial.println(ESP.getSdkVersion());
  Serial.print("MAC: ");
  Serial.println(WiFi.macAddress());
#endif
  WiFiManager wifiManager;
  //Reset setting
  //wifiManager.resetSettings();
  wifiManager.setAPStaticIPConfig(IPAddress(10, 0, 0, 1), IPAddress(10, 0, 0, 1), IPAddress(255, 255, 255, 0));
#ifdef WIFIDEBUG
  wifiManager.setDebugOutput(true);
#else
  wifiManager.setDebugOutput(false);
#endif

  if (!wifiManager.autoConnect(NETWORKNAME))
  {
#ifdef DEBUG
    Serial.println("Failed to connect");
#endif
    delay(1000);
    ESP.reset();
    delay(5000);
  }
  //Define Alexa device name
  espalexa.addDevice(DEVICE_NAME, firstLightChanged); //simplest definition, default state off
  espalexa.begin();

  //Setup outup
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
}

//Loop
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