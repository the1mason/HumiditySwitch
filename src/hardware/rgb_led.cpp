#include "hardware/rgb_led.h"
#include <Arduino.h>

int RED_PIN, GREEN_PIN, BLUE_PIN;
int RED, GREEN, BLUE;

void initRgbLed(int red_pin, int green_pin, int blue_pin) {
    RED_PIN = red_pin;
    GREEN_PIN = green_pin;
    BLUE_PIN = blue_pin;
    
    pinMode(RED_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(BLUE_PIN, OUTPUT);
}

void setRgbLed(int red, int green, int blue) {
    RED = red;
    GREEN = green;
    BLUE = blue;
    updateRgbLed();
}

void updateRgbLed() {
    analogWrite(RED_PIN, RED);
    analogWrite(GREEN_PIN, GREEN);
    analogWrite(BLUE_PIN, BLUE);
}