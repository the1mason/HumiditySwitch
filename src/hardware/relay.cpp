#include <Arduino.h>
#include "hardware/relay.h"

int _relayPin;

void initRelay(int relayPin) {
    _relayPin = relayPin;
    pinMode(relayPin, OUTPUT);
    relayOn();
    Serial.println("Relay initialized");
}

// the relay that I have is active low 
// nothing prevents me from connecting the load to the normally closed pin
// but this way LED on the relay would be flipped
// so that's better
void relayOn() {
    relaySet(LOW); 
}

void relayOff() {
    relaySet(HIGH);
}

void relaySet(bool state) {
    digitalWrite(_relayPin, state);
}