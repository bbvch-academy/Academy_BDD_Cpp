#ifndef HOME_AUTOMATION_CONTROL_H_
#define HOME_AUTOMATION_CONTROL_H_

#include <cstdint>


namespace HomeAutomation
{

class ISwitchControl;

class ITemperatureControl;

/**
  * @brief Home automation system main interface
  */
class HomeAutomationControl
{
public:
    /**
     * @brief HomeAutomationControl
     * @param light_controller Reference to the light controller
     * @param heater_controller Reference to the heater controller
     */
    HomeAutomationControl (ISwitchControl & light_controller,
                           ITemperatureControl & heater_controller);

    /**
     * @brief Switch a light on/off
     * @param light_id Id of the light
     * @param on \c true to switch the light on \c false for switching off
     */
    void switch_light (const uint32_t light_id,
                       const bool on);

    /**
     * @brief Get the currect light state
     * @param light_id Id of the light
     * @retval true light is on
     * @retval false light is off
     */
    bool light_state (const uint32_t light_id) const;


    /**
     * @brief set_room_temperature
     * @param temperature Desired room temperature
     */
    void set_room_temperature (const uint32_t temperature);

    /**
     * @brief heater_state
     * @retval true Heating
     * @retval false off
     */
    bool heater_state () const;

private:
    ISwitchControl & light_controller_;
    ITemperatureControl & heater_controller_;

};


} // namespace HomeAutomation

#endif //HOME_AUTOMATION_CONTROL_H_
