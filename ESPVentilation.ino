#include <ESP8266WiFi.h>
#include <WiFiManager.h>
#include <EEPROM.h>
#include <Espalexa.h>
#include "config.h"

WiFiClient wifiClient;
Espalexa espalexa;

void stateChanged(uint8_t value);

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
  wifiManager.setAPStaticIPConfig(IPAddress(IPLOWA, IPLOWB, IPLOWC, IPLOWD), IPAddress(IPHIGHA, IPHIGHB, IPHIGHC, IPHIGHD), IPAddress(255, 255, 255, 0));
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
    delay(ATTENPTING);
    ESP.reset();
    delay(5000);
  }
  //Define Alexa device name
  espalexa.addDevice(DEVICE_NAME, stateChanged);
  espalexa.begin();

  //ESP8266 Configuration
  pinMode(GPIO_0, OUTPUT);
  digitalWrite(GPIO_0, HIGH);
}

//Loop
void loop()
{
  espalexa.loop();
  delay(1);
}

//our callback functions
void stateChanged(uint8_t value)
{
  if (value > 0)
    digitalWrite(GPIO_0, LOW);

  if (value == 0)
    digitalWrite(GPIO_0, HIGH);

#ifdef DEBUG
  Serial.print("value: ");
  Serial.println(value);
#endif
}