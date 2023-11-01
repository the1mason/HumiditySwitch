#ifndef RGB_LED_H
#define RGB_LED_H

void initRgbLed(int red_pin, int green_pin, int blue_pin);

void setRgbLed(int red, int green, int blue);

void updateRgbLed();

#endif // RGB_LED_H