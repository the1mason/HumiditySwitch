#ifndef INDICATOR_H
#define INDICATOR_H

void indicatorOverrideMode(bool mode);

void flipIndicatorOverrideMode();

void indicateError();

void indicateCriticalError();

void indicateOn();

void indicateOff();

void initIndicator(int red_pin, int green_pin, int blue_pin);

void setBlinkingLed(int red, int green, int blue);

void updateIndicator();

bool indicatorTimerCallback(void* argument);

#endif // INDICATOR_H