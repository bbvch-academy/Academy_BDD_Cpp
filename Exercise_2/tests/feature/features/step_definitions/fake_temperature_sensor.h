#ifndef FAKE_TEMPERATURE_SENSOR_H_
#define FAKE_TEMPERATURE_SENSOR_H_

#include "temperature_sensor_interface.h"

namespace HomeAutomationFeatureTests
{

class FakeTemperatureSensor :
    public HomeAutomation::ITemperatureSensor
{
public:
    FakeTemperatureSensor () :
        temperature_(0)
    {
    }

    virtual uint32_t get_temperature () const
    {
        return temperature_;
    }

    void set_temperature (uint32_t temperature)
    {
        temperature_ = temperature;
    }

private:
    uint32_t temperature_;
};

}

#endif //FAKE_TEMPERATURE_SENSOR_H_
