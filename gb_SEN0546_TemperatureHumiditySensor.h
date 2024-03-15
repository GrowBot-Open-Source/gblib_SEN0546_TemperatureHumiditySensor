#ifndef gb_SEN0546_TemperatureHumiditySensor_h
#define gb_SEN0546_TemperatureHumiditySensor_h

#include <Arduino.h>

class gb_SEN0546_TemperatureHumiditySensor
{
private:
    double humidity;
    double temperature;

public:
    gb_SEN0546_TemperatureHumiditySensor;

    // get rel humidity
    double getHumidity();

    // get temperature
    double getTemperature();

    // get VPD
    double getVpd(double humidity, double temperature);
};

#endif