#ifndef HANDLERS_H
#define HANDLERS_H

void initHandlers(ESP8266WebServer* server);

void handleIndex();
void handleMessage(String message);
void handleIndicatorOverride();
void handleNotFound();
void handleBadRequest(String message);
void handleSensor();


#endif // HANDLERS_H