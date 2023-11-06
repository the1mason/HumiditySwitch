#ifndef SWITCH_H
#define SWITCH_H

extern bool switchState;
extern int switchOverrideState;
extern int switchMinHumidity;
extern int switchMaxHumidity;

void initSwitch(int relayPin, int timerInterval, int minHumidity, int maxHumodity);

void overrideSwitch(int state);

void updateSwitch();

void loopSwitch();

bool switchTimerCallback(void* argument);

void sensorBasedSwitch();

void overrideBasedSwitch();

#endif // SWITCH_H