#ifndef HANDLERS_H
#define HANDLERS_H

void initHandlers(ESP8266WebServer* server);

void handleIndex();
void handleLed();
void handleNotFound();

#endif // HANDLERS_H