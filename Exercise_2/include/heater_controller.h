#ifndef HEATER_CONTROLLER_H_
#define HEATER_CONTROLLER_H_

#include <cstdint>
#include <boost/date_time/posix_time/posix_time_types.hpp>

#include "scheduler_interface.h"
#include "temperature_control_interface.h"


namespace HomeAutomation
{

class ITimeService;

class ITemperatureSensor;

class IDigitalIO;

/**
 * @brief The HeaterController class
 */
class HeaterController :
    public IScheduler,
    public ITemperatureControl
{
public:
    /**
     * @brief HeaterController
     */
    HeaterController (IDigitalIO & heater,
                      ITemperatureSensor & temperature_sensor,
                      ITimeService & timer);

    /**
     * @copydoc IScheduler::wakeup
     */
    virtual void wakeup ();

    /**
     * @copydoc ITemperatureControl::set_target_temperature
     */
    virtual void set_target_temperature (uint32_t temperature);

    /**
     * @copydoc ITemperatureControl::get_current_temperature
     */
    virtual uint32_t get_current_temperature () const;

    /**
     * @copydoc ITemperatureControl::get_heater_state
     */
    virtual bool get_heater_state () const;

private:
    IDigitalIO & heater_;
    ITemperatureSensor & temperature_sensor_;
    ITimeService & time_service_;

    uint32_t target_temperature_;

    static const boost::posix_time::time_duration sensor_polling_intervall;
};


} // namespace HomeAutomation

#endif //HEATER_CONTROLLER_H_
