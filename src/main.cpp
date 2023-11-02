#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Wire.h>
#include "api/handlers.h"
#include "indicator.h"
#include "hardware/aht10.h"

const char *WIFI_SSID = "8HYeW6wfv1kPh8eTTw";
const char *WIFI_PASSWORD = "SzU9Ktnd4rQnmC8Uzk";

const int AHT10_SDA = 4;
const int AHT10_SCL = 5;

const int RGB_LED_R = 14;
const int RGB_LED_G = 12;
const int RGB_LED_B = 13;

ESP8266WebServer server(80);

enum WifiState
{
  DISCONNECTED,
  CONNECTING,
  CONNECTED
};

WifiState wifiState = DISCONNECTED;

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    continue;

  initIndicator(RGB_LED_R, RGB_LED_G, RGB_LED_B);
  initAht10();
  initHandlers(&server);
  server.begin();
}

void loop()
{
  bool connectWifi();
  if (!connectWifi())
  {
    return;
  }

  server.handleClient();
  updateIndicator();
}

bool connectWifi()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    if (wifiState != CONNECTED)
    {
      Serial.println("WiFi is connected");
      wifiState = CONNECTED;
      indicateOn();
    }
    return true;
  }

  if (wifiState == CONNECTING)
  {
    return false;
  }

  if (WiFi.status() == WL_WRONG_PASSWORD || WiFi.status() == WL_NO_SSID_AVAIL)
  {
    wifiState = DISCONNECTED;
    return false;
  }

  Serial.println("WiFi is not connected. Connecting...");
  indicateError();
  wifiState = CONNECTING;
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  return false;
}