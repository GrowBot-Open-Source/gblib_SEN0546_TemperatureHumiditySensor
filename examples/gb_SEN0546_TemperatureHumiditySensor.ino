#include <gb_SEN0546_TemperatureHumiditySensor.h>

gb_SEN0546_TemperatureHumiditySensor tempHumidity;

void setup()
{
    Serial.begin(9600);
    tempHumidity.setupTemperatureHumiditySensor();
};

void loop()
{
    hum = tempHumidity.getHumidity;
    temp = tempHumidity.getTemperature;
    vpd = tempHumidity.calculateVPD(temp, hum);

    Serial.print(temp);
    Serial.print("\t");
    Serial.print(hum);
    Serial.print("\t");
    Serial.println(vpd);
};
