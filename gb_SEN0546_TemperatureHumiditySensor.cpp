/*********************************************************************
 * gb_SEN0546_TemperatureHumiditySensor.cpp
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

#include "gb_SEN0546_TemperatureHumiditySensor.h"
#include <Arduino.h>
#include <Wire.h>
#include <math.h>
#define address 0x40

char dtaUart[15];
char dtaLen = 0;
uint8_t Data[100] = {0};
uint8_t buff[100] = {0};

uint8_t buf[4] = {0};
uint16_t data, data1;

// create TemperatureHumiditySensor object
gb_SEN0546_TemperatureHumiditySensor::gb_SEN0546_TemperatureHumiditySensor();

// setup sensor
void gb_SEN0546_TemperatureHumiditySensor::setupTemperatureHumiditySensor()
{
    Wire.begin();
    Serial.begin(9600);
}

// read sensor
uint8_t gb_SEN0546_TemperatureHumiditySensor::readTemperatureHumiditySensor(uint8_t reg, const void *pBuf, size_t size)
{
    if (pBuf == NULL)
    {
        Serial.println("pBuf ERROR!! : null pointer");
    }
    uint8_t *_pBuf = (uint8_t *)pBuf;
    Wire.beginTransmission(address);
    Wire.write(&reg, 1);
    if (Wire.endTransmission() != 0)
    {
        return 0;
    }
    delay(20);
    Wire.requestFrom(address, (uint8_t)size);
    for (uint16_t i = 0; i < size; i++)
    {
        _pBuf[i] = Wire.read();
    }
    return size;
}

// get rel humidity
float gb_SEN0546_TemperatureHumiditySensor::getHumidity()
{
    readTemperatureHumiditySensor(0x00, buf, 4);
    data1 = buf[2] << 8 | buf[3];
    humidity = ((float)data1 / 65535.0) * 100;
    return humidity;
    delay(500);
}

// get temperature
float gb_SEN0546_TemperatureHumiditySensor::getTemperature()
{
    readTemperatureHumiditySensor(0x00, buf, 4);
    data = buf[0] << 8 | buf[1];
    temperature = ((float)data * 165 / 65535.0) - 40.0;
    return temperature;
}

// calculate saturated vapor pressure
float gb_SEN0546_TemperatureHumiditySensor::calculateSaturatedVaporPressure(float temperature)
{
    const float A = 17.27;
    const float B = 237.7;
    float saturatedVaporPressure = 0.611 * exp((A * temperature) / (temperature + B));
    return saturatedVaporPressure;
}

// get vpd
float gb_SEN0546_TemperatureHumiditySensor::getVPD(float temperature, float humidity)
{
    float saturatedVaporPressure = calculateSaturatedVaporPressure(temperature);
    float vpd = saturatedVaporPressure - (humidity / 100.0 * saturatedVaporPressure);
    return vpd;
}

float gb_SEN0546_TemperatureHumiditySensor::getVPD()
{
    readTemperatureHumiditySensor(0x00, buf, 4);
    data = buf[0] << 8 | buf[1];
    data1 = buf[2] << 8 | buf[3];
    temperature = (((float)data * 165 / 65535.0) - 40.0);
    humidity = (((float)data1 / 65535.0) * 100);
    float saturatedVaporPressure = calculateSaturatedVaporPressure((((float)data * 165 / 65535.0) - 40.0));
    float vpd = saturatedVaporPressure - ((((float)data1 / 65535.0) * 100) / 100.0 * saturatedVaporPressure);
    return vpd;
}