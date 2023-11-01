#include <Arduino.h>
#include <ESP8266WebServer.h>
#include "api/handlers.h"
#include "indicator.h"

ESP8266WebServer* serverPtr = NULL;
bool _overrideMode = false;

void initHandlers(ESP8266WebServer* server) {
  void handleIndex();
  void handleIndicator();
  void handleIndicatorOverride();
  void handleNotFound();
  
  serverPtr = server;

  serverPtr->on("/", handleIndex);
  serverPtr->on("/indicate", handleIndicator);
  serverPtr->on("/override", handleIndicatorOverride);
  serverPtr->onNotFound(handleNotFound);
}

void handleLed() 
{
  handleIndex();
}

void handleIndicator() 
{
  void handleBadRequest(String);

  if (serverPtr->args() < 1) {
    handleBadRequest("Expected 1 argument");
  }
  
  String state = serverPtr->arg(0);

  if (state == "on") {
    indicateOn();
  } else if (state == "off") {
    indicateOff();
  } else if (state == "error") {
    indicateError();
  } else if (state == "critical_error") {
    indicateCriticalError();
  } else {
    handleBadRequest("Invalid state");
  }

  handleIndex();
}

void handleIndicatorOverride() 
{
  _overrideMode = !_overrideMode;
  indicatorOverrideMode(_overrideMode);
  handleIndex();
}

void handleIndex() {
  String response = "{\"status\": 200}";
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
