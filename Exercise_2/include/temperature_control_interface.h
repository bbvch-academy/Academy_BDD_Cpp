#ifndef TEMPERATURE_CONTROL_INTERFACE_H_
#define TEMPERATURE_CONTROL_INTERFACE_H_

#include <cstdint>

namespace HomeAutomation
{

/**
 * @brief Interface for a temperature controller
 */
class ITemperatureControl
{
public:
    /**
     * @brief ~ITemperatureControl
     */
    virtual ~ITemperatureControl ()
    {}

    /**
     * @brief Set the desired temperature
     * @param temperature desired temperature
     */
    virtual void set_target_temperature (uint32_t temperature) = 0;

    /**
     * @brief Get the current temperature
     * @return
     */
    virtual uint32_t get_current_temperature () const = 0;

    /**
     * @brief get_heater_state
     * @retval true Heater is ON (heating)
     * @retval false Heater is OFF
     */
    virtual bool get_heater_state () const = 0;

protected:
    /**
     * Assignment of abstract type is not allowed
    */
    ITemperatureControl & operator= (const ITemperatureControl &);
};


} // namespace HomeAutomation

#endif //TEMPERATURE_CONTROL_INTERFACE_H_
