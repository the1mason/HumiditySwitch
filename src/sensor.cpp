#include <Arduino.h>
#include <AHT10.h>
#include <arduino-timer.h>
#include "sensor.h"
#include "indicator.h"

float sensorTemperature, sensorHumidity;

Timer<> sensorTimer;
AHT10 aht10(AHT10_ADDRESS_0X38);

void initSensor()
{
    while (aht10.begin() != true)
    {
        Serial.println(F("AHT10 is not connected or failed to load calibration coefficient"));
        indicateCriticalError();
        delay(5000);
    }

    sensorTimer.every(10000, sensorTimerCallback);
    Serial.printf_P("AHT10 initialized!");
}

void loopSensor()
{
    sensorTimer.tick();
}

void readSensor()
{
    sensorHumidity = aht10.readHumidity(AHT10_FORCE_READ_DATA);
    sensorTemperature = aht10.readTemperature(AHT10_USE_READ_DATA);
}

bool sensorTimerCallback(void *argument)
{
    readSensor();
    return true;
}