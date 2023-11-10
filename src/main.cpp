#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include <Wire.h>
#include <Button2.h>
#include "api/handlers.h"
#include "indicator.h"
#include "switch.h"
#include "sensor.h"

const char *WIFI_SSID = "";
const char *WIFI_PASSWORD = "";

const int AHT10_SDA = 4;
const int AHT10_SCL = 5;

const int BUTTON_PIN = 2;

const int RELAY_PIN = 0;
const int SWITCH_UPDATE_TIME = 10000;

// TODO: Move to EEPROM
const float SWITCH_HUMIDITY_MIN_THRESHOLD = 40.0;
const float SWITCH_HUMIDITY_MAX_THRESHOLD = 60.0;

const int RGB_LED_R = 14;
const int RGB_LED_G = 12;
const int RGB_LED_B = 13;

enum WifiState
{
  DISCONNECTED,
  CONNECTING,
  CONNECTED
};

Button2 modeOverrideButton;
ESP8266WebServer server(80);
WifiState wifiState = DISCONNECTED;

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    continue;

  initIndicator(RGB_LED_R, RGB_LED_G, RGB_LED_B);
  initSensor();
  initSwitch(RELAY_PIN, SWITCH_UPDATE_TIME, SWITCH_HUMIDITY_MIN_THRESHOLD, SWITCH_HUMIDITY_MAX_THRESHOLD);

  void modeOverrideForceOnCallback(Button2&);
  void modeOverrideForceOffCallback(Button2&);
  void modeOverrideClearCallback(Button2&);
  modeOverrideButton.begin(BUTTON_PIN, INPUT_PULLUP);
  modeOverrideButton.setClickHandler(modeOverrideForceOnCallback);
  modeOverrideButton.setDoubleClickHandler(modeOverrideForceOffCallback);
  modeOverrideButton.setLongClickHandler(modeOverrideClearCallback);

  initHandlers(&server);
  server.begin();
}

void loop()
{
  modeOverrideButton.loop();
  loopIndicator();
  loopSensor();
  loopSwitch();

  bool connectWifi();
  if (!connectWifi())
  {
    return;
  }

  server.handleClient();
}

void modeOverrideForceOnCallback(Button2& btn)
{
  overrideSwitch(1);
}

void modeOverrideForceOffCallback(Button2& btn)
{
  overrideSwitch(2);
}

void modeOverrideClearCallback(Button2& btn)
{
  overrideSwitch(0);
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