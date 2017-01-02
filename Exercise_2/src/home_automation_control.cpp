#include "home_automation_control.h"
#include "switch_control_interface.h"
#include "temperature_control_interface.h"


namespace HomeAutomation
{

HomeAutomationControl::HomeAutomationControl (ISwitchControl & light_controller,
                                              ITemperatureControl & heater_controller) :
    light_controller_(light_controller),
    heater_controller_(heater_controller)
{

}


void HomeAutomationControl::switch_light (const uint32_t light_id,
                                          const bool on)
{
    if (on)
    {
        light_controller_.switch_on(light_id);
    }
    else
    {
        light_controller_.switch_off(light_id);
    }
}

bool HomeAutomationControl::light_state (const uint32_t light_id) const
{
    return light_controller_.switch_state(light_id);
}

void HomeAutomationControl::set_room_temperature (const uint32_t temperature)
{
    heater_controller_.set_target_temperature(temperature);
}

bool HomeAutomationControl::heater_state () const
{
    return heater_controller_.get_heater_state();
}


} // namespace HomeAutomation
