#include <Arduino.h>
#include "indicator.h"
#include "hardware/rgb_led.h"

void override(bool mode) {

}

void error() {

}

void criticalError() {

}

void on() {

}

void off() {

}

void timer() { 

}

void initIndicator(int red_pin, int green_pin, int blue_pin) {
    initRgbLed(red_pin, green_pin, blue_pin);
}

void updateIndicator() {

}