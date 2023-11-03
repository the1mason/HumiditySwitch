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

void updateIndicator()
{
    timer.tick();
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

void indicateError()
{
    indicatorState = ERROR;
    indicatorTimerCallback(nullptr);
}

void indicateCriticalError()
{
    indicatorState = CRITICAL_ERROR;
    indicatorTimerCallback(nullptr);
}

void indicateOn()
{
    indicatorState = ON;
    indicatorTimerCallback(nullptr);
}

void indicateOff()
{
    indicatorState = OFF;
    indicatorTimerCallback(nullptr);
}
