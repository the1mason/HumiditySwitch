#ifndef RELAY_H
#define RELAY_H

void initRelay(int relayPin);

void relayOn();

void relayOff();

void relaySet(bool state);

#endif // RELAY_H