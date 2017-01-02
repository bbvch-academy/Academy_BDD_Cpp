#ifndef TEMPERATURE_SENSOR_MOCK_H
#define TEMPERATURE_SENSOR_MOCK_H

#include <gmock/gmock.h>

#include "temperature_sensor_interface.h"

namespace
{

class TemperatureSensorMock :
    public HomeAutomation::ITemperatureSensor
{
public:
    MOCK_CONST_METHOD0(get_temperature, uint32_t());
};

} // namespace

#endif //TEMPERATURE_SENSOR_MOCK_H
