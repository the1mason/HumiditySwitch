#include <Arduino.h>
#include <arduino-timer.h>
#include "indicator.h"
#include "hardware/rgb_led.h"

bool overrideMode = false;
bool overrideLedFlip = false;

enum IndicatorState
{
    ERROR,
    CRITICAL_ERROR,
    ON,
    OFF
};

IndicatorState indicatorState = ON;

Timer<> timer;

void initIndicator(int red_pin, int green_pin, int blue_pin)
{
    initRgbLed(red_pin, green_pin, blue_pin);
    timer = timer_create_default();
    timer.every(500, indicatorTimerCallback);
}

void loopIndicator() {
    timer.tick();
}

void updateIndicator()
{
    switch (indicatorState)
    {
    case ON:
        setBlinkingLed(0, 255, 0);
        break;
    case OFF:
        setBlinkingLed(0, 0, 0);
        break;
    case ERROR:
        setRgbLed(255, 64, 0);
        break;
    case CRITICAL_ERROR:
        setRgbLed(255, 0, 0);
        break;
    default:
        break;
    }
}

void indicatorOverrideMode(bool mode)
{
    overrideMode = mode;
}

void flipIndicatorOverrideMode()
{
    indicatorOverrideMode(!overrideMode);
}

bool indicatorTimerCallback(void* argument)
{
    updateIndicator();
    return true;
}


void setBlinkingLed(int red, int green, int blue)
{
    if(overrideLedFlip && overrideMode)
    {
        setRgbLed(0, 255, 255);
    }
    else
    {
        setRgbLed(red, green, blue);
    }
    overrideLedFlip = !overrideLedFlip;
}

#pragma region Update indicator

void indicateError()
{
    indicatorState = ERROR;
    updateIndicator();
}

void indicateCriticalError()
{
    indicatorState = CRITICAL_ERROR;
    updateIndicator();
}

void indicateOn()
{
    indicatorState = ON;
    updateIndicator();
}

void indicateOff()
{
    indicatorState = OFF;
    updateIndicator();
}

#pragma endregion