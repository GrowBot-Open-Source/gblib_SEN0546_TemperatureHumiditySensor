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
