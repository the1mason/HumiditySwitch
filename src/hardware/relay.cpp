#include <Arduino.h>
#include "hardware/relay.h"

int _relayPin;

void initRelay(int relayPin) {
    _relayPin = relayPin;
    pinMode(relayPin, OUTPUT);
    digitalWrite(relayPin, LOW);
}

void relayOn() {
    relaySet(HIGH);
}

void relayOff() {
    relaySet(LOW);
}

void relaySet(bool state) {
    digitalWrite(_relayPin, state);
    Serial.println(digitalRead(_relayPin));
}