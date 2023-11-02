#ifndef HANDLERS_H
#define HANDLERS_H

void initHandlers(ESP8266WebServer* server);

void handleIndex();
void handleMessage(String message);
void handleIndicator();
void handleIndicatorOverride();
void handleNotFound();
void handleBadRequest(String message);
void handleAht();


#endif // HANDLERS_H