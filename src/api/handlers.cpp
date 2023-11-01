#include <Arduino.h>
#include <ESP8266WebServer.h>
#include "api/handlers.h"

ESP8266WebServer* serverPtr = NULL;

void initHandlers(ESP8266WebServer* server) {
  void handleIndex();
  void handleLed();
  void handleNotFound();
  
  serverPtr = server;

  serverPtr->on("/", handleIndex);
  serverPtr->on("/led", handleLed);
  serverPtr->onNotFound(handleNotFound);
}

void handleIndex() {
  String led = "false";
  if (true) {
    led = "true";
  }
  String response = "{\"status\": 200,\"led\": ";
  response += led;
  response += "}";
  serverPtr->send(200, "application/json", response);
}

void handleLed() 
{
  handleIndex();
}

void handleNotFound()
{
  serverPtr->send(404, "application/json", "{\"status\": 404,\"error\": \"not found\"}");
}