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
    Serial.println("Switch initialized");
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

        // When override mode is disabled, we need to update the relay and indicator to the last known state
        if (switchState)
        {
            relayOn();
            indicateOn();
        }
        else
        {
            relayOff();
            indicateOff();
        }

        updateSwitch();
        return;
    }

    indicatorOverrideMode(true);
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
        indicateOn();
        switchState = true;
        return;
    }
    else if (sensorHumidity >= switchMaxHumidity)
    {
        relayOff();
        indicateOff();
        switchState = false;
        return;
    }
}

void overrideBasedSwitch()
{
    if (switchOverrideState == 1)
    {
        relayOn();
        indicateOn();
        return;
    }

    if (switchOverrideState == 2)
    {
        relayOff();
        indicateOff();
        return;
    }
}
