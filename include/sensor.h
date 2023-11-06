#ifndef SENSOR_H
#define SENSOR_H

extern float sensorTemperature;
extern float sensorHumidity;

void initSensor();

void loopSensor();

void readSensor();

bool sensorTimerCallback(void* argument);

#endif // SENSOR.H