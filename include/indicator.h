#ifndef INDICATOR_H
#define INDICATOR_H

void override(bool mode);

void error();

void criticalError();

void on();

void off();

void timer();

void initIndicator(int red_pin, int green_pin, int blue_pin);

void updateIndicator();

#endif // INDICATOR_H