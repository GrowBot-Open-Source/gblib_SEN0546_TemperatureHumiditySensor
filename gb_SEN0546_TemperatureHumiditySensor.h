/*********************************************************************
 * gb_SEN0546_TemperatureHumiditySensor.h
 *
 * Copyright (C)    20124   [GrowBot Open Source],
 * GitHub Link :XXXXX
 * This Library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Description:Implement DFRobot SEN0546 temperature and humidity sensor into the growbot system
 *
 * Product Links：
 *
 * Sensor driver pin：
 *
 * author  :  GrowBot
 * version :  V1.0
 * date    :  2024-05-14
 **********************************************************************/

#ifndef gb_SEN0546_TemperatureHumiditySensor_h
#define gb_SEN0546_TemperatureHumiditySensor_h

#include <Wire.h>
#include <Arduino.h>

class gb_SEN0546_TemperatureHumiditySensor
{
private:
    float humidity;
    float temperature;
    float vpd;

public:
    gb_SEN0546_TemperatureHumiditySensor(){};

    // setup sensor
    void setupTemperatureHumiditySensor();

    // read sensor
    uint8_t readTemperatureHumiditySensor(uint8_t reg, const void *pBuf, size_t size);

    // get rel humidity
    float getHumidity();

    // get temperature
    float getTemperature();

    // calculate saturated vapor pressure
    float calculateSaturatedVaporPressure(float temperature);

    // get VPD
    float calculateVPD(float temperature, float humidity);
};

#endif