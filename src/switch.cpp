#include <Arduino.h>
#include <arduino-timer.h>
#include "hardware/relay.h"
#include "switch.h"
#include "indicator.h"
#include "sensor.h"

bool switchState;
int switchOverrideState;
int switchMinHumidity;
int switchMaxHumidity;

Timer<> switchTimer;

void initSwitch(int relayPin, int timerInterval, int minHumidity, int maxHumidity)
{
    initRelay(relayPin);
    switchMinHumidity = minHumidity;
    switchMaxHumidity = maxHumidity;
    switchTimer.every(timerInterval, switchTimerCallback);
}

void loopSwitch()
{
    switchTimer.tick();
}

void overrideSwitch(int state)
{
    switchOverrideState = state;
    if (state == 0)
    {
        indicatorOverrideMode(false);
    }
    else
    {
        indicatorOverrideMode(true);
    }
    updateSwitch();
}

void updateSwitch()
{
    if (switchOverrideState == 0)
    {
        sensorBasedSwitch();
    }
    else
    {
        overrideBasedSwitch();
    }
}

bool switchTimerCallback(void *argument)
{
    updateSwitch();
    return true;
}

void sensorBasedSwitch()
{
    if (sensorHumidity <= switchMinHumidity)
    {
        relayOn();
        switchState = true;
    }
    else if (sensorHumidity >= switchMaxHumidity)
    {
        relayOff();
        switchState = false;
    }
}

void overrideBasedSwitch()
{
    if (switchOverrideState == 1)
    {
        relayOn();
        switchState = true;
        return;
    }

    if (switchOverrideState == 2)
    {
        relayOff();
        switchState = false;
        return;
    }
}
