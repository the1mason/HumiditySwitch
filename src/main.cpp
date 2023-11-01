#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "api/handlers.h"
#include "indicator.h"

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

  Serial.print("Connecting to");
  Serial.println(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");

  initHandlers(&server);

  server.begin();
}

void loop()
{
  server.handleClient();
  updateIndicator();
}