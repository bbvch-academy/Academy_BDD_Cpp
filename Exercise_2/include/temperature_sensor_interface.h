#ifndef TEMPERATURE_SENSOR_INTERFACE_H_
#define TEMPERATURE_SENSOR_INTERFACE_H_

#include <cstdint>

namespace HomeAutomation
{

/**
 * @brief Temperature sensor interface
 */
class ITemperatureSensor
{
public:

    /**
     * @brief ~ITemperatureSensor
     */
    virtual ~ITemperatureSensor ()
    {}

    /**
     * @brief Return the current temperature in °C
     * @return Current temperature in °C
     */
    virtual uint32_t get_temperature () const = 0;

protected:
    /**
     * Assignment of abstract type is not allowed
    */
    ITemperatureSensor & operator= (const ITemperatureSensor &);
};


} // namespace HomeAutomation

#endif //TEMPERATURE_SENSOR_INTERFACE_H_
