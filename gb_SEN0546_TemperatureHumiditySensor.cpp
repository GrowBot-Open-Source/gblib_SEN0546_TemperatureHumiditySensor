#include "gb_SEN0546_TemperatureHumiditySensor.h"

gb_SEN0546_TemperatureHumiditySensor;

// get rel humidity
double getHumidity();

// get temperature
double getTemperature();

// get VPD
double getVpd(double humidity, double temperature);
}
;

#include "Wire.h"
#define address 0x40
char dtaUart[15];
char dtaLen = 0;
uint8_t Data[100] = {0};
uint8_t buff[100] = {0};
void setup()
{
    Serial.begin(9600);
    Wire.begin();
}
uint8_t buf[4] = {0};
uint16_t data, data1;
float temp;
float hum;
void loop()
{
    readReg(0x00, buf, 4);
    data = buf[0] << 8 | buf[1];
    data1 = buf[2] << 8 | buf[3];
    temp = ((float)data * 165 / 65535.0) - 40.0;
    hum = ((float)data1 / 65535.0) * 100;
    Serial.print("temp(C):");
    Serial.print(temp);
    Serial.print("\t");
    Serial.print("hum(%RH):");
    Serial.println(hum);
    delay(500);
}
uint8_t readReg(uint8_t reg, const void *pBuf, size_t size)
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

// Sample Multiplexer
/*!
 * file Multi_SSD1306.ino
 *
 * Download Display library https://github.com/DFRobot/DFRobot_Display.git
 * Download SSD1306 library https://github.com/DFRobot/DFRobot_SSD1306.git
 *
 * Connect the 2 SSD1306 devices to the port 0 and  port 1 on the i2cmultiplexer respectively and then connect the I2cmultiplexer and Arduino, download this sample.
 * @n The address of I2C and the name of SSD1306 display module can be seen
 *
 * Copyright   [DFRobot](https://www.dfrobot.com), 2016
 * Copyright   GNU Lesser General Public License
 *
 * version  V0.1
 * date  2018-5-10
 */
#include "DFRobot_SSD1306_I2C.h"
#include "DFRobot_I2CMultiplexer.h"
#include "DFRobot_Character.h"
#include "DFRobot_GT30L.h"
#include <Wire.h>
#include <SPI.h>

/*Create an OLED object, the address is 0x3c*/
DFRobot_SSD1306_I2C OLED(0x3c);

/*Create an I2C Multiplexer object, the address of I2C Multiplexer is 0X70*/
DFRobot_I2CMultiplexer I2CMulti(0x70);

void setup(void)
{
    /*Let the OLED on port 0 display characters*/
    I2CMulti.selectPort(0); // Select port
    OLED.begin();           // initialize OLED
    OLED.setTextColor(1);
    OLED.setTextSize(2);

    OLED.setCursor(0, 0);   // Set the corrdianate of characters
    OLED.print("device A"); // Display characters
    OLED.setCursor(0, 30);
    OLED.print("addr:0x3C");

    /*Let OLED on  port 1 display  characters */
    I2CMulti.selectPort(1);
    OLED.begin();
    OLED.setTextColor(1);
    OLED.setTextSize(2);

    OLED.setCursor(0, 0);
    OLED.print("device B");
    OLED.setCursor(0, 30);
    OLED.print("addr:0x3C");
}

void loop(void)
{
}