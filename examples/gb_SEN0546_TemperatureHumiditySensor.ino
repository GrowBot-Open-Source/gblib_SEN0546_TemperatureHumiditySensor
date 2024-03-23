#include <gb_SEN0546_TemperatureHumiditySensor.h>

gb_SEN0546_TemperatureHumiditySensor tempHumidity;

void setup()
{
    Serial.begin(9600);
    tempHumidity.setupTemperatureHumiditySensor();
};

void loop()
{
    float temp = tempHumidity.getHumidity();
    float hum = tempHumidity.getTemperature();
    float vpd = tempHumidity.calculateVPD(temp, hum);

    Serial.print(tempHumidity.getHumidity());
    Serial.print("\t");
    Serial.print(tempHumidity.getTemperature());
    Serial.print("\t");
    Serial.println(vpd);
    delay(1000);
};
