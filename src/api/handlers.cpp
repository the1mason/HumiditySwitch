#include <Arduino.h>
#include <ESP8266WebServer.h>
#include "api/handlers.h"
#include "indicator.h"
#include "sensor.h"
#include "switch.h"

ESP8266WebServer *serverPtr = NULL;
bool _overrideMode = false;

void initHandlers(ESP8266WebServer *server)
{
  serverPtr = server;

  serverPtr->on("/", handleIndex);
  serverPtr->on("/override", handleIndicatorOverride);
  serverPtr->on("/sensor", handleSensor);
  serverPtr->onNotFound(handleNotFound);
  Serial.println("Handlers initialized");
}

void handleIndicatorOverride()
{
  if (serverPtr->args() < 1)
  {
    handleBadRequest("Expected 1 argument");
  }

  if (serverPtr->arg(0) != "0" || serverPtr->arg(0) != "1" || serverPtr->arg(0) != "2")
  {
    overrideSwitch(serverPtr->arg(0).toInt());
    handleMessage("Set override mode to " + serverPtr->arg(0));
  }
  handleBadRequest("Invalid argumeent: expected integer from 0 to 2");
}

void handleIndex()
{
  String response =
      "{\"status\": 200, \"overrideState\": " + String(switchOverrideState) +
      ", \"humidity\": " + String(sensorHumidity) +
      ", \"sensorTemperature\": " + String(sensorTemperature) + "}";

  serverPtr->send(200, "application/json", response);
}

void handleMessage(String message)
{
  String response = "{\"status\": 200, \"message\": \"" + message + "\"}";
  serverPtr->send(200, "application/json", response);
}

void handleSensor()
{
  String response =
      "{\"status\": 200, \"humidity\": " + String(sensorHumidity) +
      ", \"sensorTemperature\": " + String(sensorTemperature) + "}";
  serverPtr->send(200, "application/json", response);
}

void handleNotFound()
{
  serverPtr->send(404, "application/json", "{\"status\": 404,\"error\": \"not found\"}");
}

void handleBadRequest(String message)
{
  serverPtr->send(400, "application/json", "{\"status\": 400,\"error\": \"" + message + "\"}");
}
