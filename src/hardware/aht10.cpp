#include "hardware/aht10.h"
#include <AHT10.h>
#include "indicator.h"
float aht10Temperature, aht10Humidity;

AHT10 aht10(AHT10_ADDRESS_0X38);

void initAht10()
{
  while (aht10.begin() != true)
  {
    Serial.println(F("AHT10 is not connected or failed to load calibration coefficient")); //(F()) save string to flash & keeps dynamic memory free
    indicateCriticalError();
    delay(5000);
  }
  Serial.printf_P("AHT10 initialized!");
}

void readAht10()
{
    aht10Humidity = aht10.readHumidity(AHT10_FORCE_READ_DATA);
    aht10Temperature = aht10.readTemperature(AHT10_USE_READ_DATA);
}