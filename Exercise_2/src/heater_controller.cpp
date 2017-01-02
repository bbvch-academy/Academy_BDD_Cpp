#include "heater_controller.h"
#include "temperature_sensor_interface.h"
#include "time_service_interface.h"
#include "digital_io_interface.h"


namespace HomeAutomation
{

const boost::posix_time::time_duration HeaterController::sensor_polling_intervall = boost::posix_time::minutes(1);

HeaterController::HeaterController (IDigitalIO & heater,
                                    ITemperatureSensor & temperature_sensor,
                                    ITimeService & timer) :
    heater_(heater),
    temperature_sensor_(temperature_sensor),
    time_service_(timer),
    target_temperature_(0)
{

}


void HeaterController::wakeup ()
{
    if (get_current_temperature() < target_temperature_)
    {
        heater_.set(true);
    }
    else
    {
        heater_.set(false);
    }
}

void HeaterController::set_target_temperature (uint32_t temperature)
{
    time_service_.set_periodic_alarm(sensor_polling_intervall, this);
    target_temperature_ = temperature;
    wakeup();
}

uint32_t HeaterController::get_current_temperature () const
{
    return temperature_sensor_.get_temperature();
}

bool HeaterController::get_heater_state () const
{
    return heater_.get();
}

} // namespace HomeAutomation
