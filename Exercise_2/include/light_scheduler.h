#ifndef LIGHT_SCHEDULER_H_
#define LIGHT_SCHEDULER_H_

#include <cstdint>
#include <map>
#include <string>

#include "scheduler_interface.h"


namespace HomeAutomation
{

class ITimeService;

class ISwitchControl;

/**
 * @brief The Time struct used to save a time schedule
 */
struct TimeOfDay
{
    /**
     * @brief Create a TimeOfDay struct from a string
     * @param time_as_string Time as string
     * @return TimeOfDay struct
    */
    static TimeOfDay from_string (std::string time_as_string);

    int32_t hour; ///< hour part of the time
    int32_t minute; ///< minute part of the time
};

/**
 * @brief The TimeCompare struct used as compare function of the maps having struct Time as key
 */
struct TimeCompare
{
    /**
     * @brief operator ()
     * @param lhs
     * @param rhs
     * @return
     */
    bool operator() (const TimeOfDay & lhs, const TimeOfDay & rhs)
    {
        if (lhs.hour == rhs.hour)
        {
            return (lhs.minute < rhs.minute);
        }
        return lhs.hour < rhs.hour;
    }
};

/**
 * @brief The LightScheduleAction struct used to save the action to perform at a schedule
 */
struct LightScheduleAction
{
    uint32_t light_id;  ///< Light id to switch on/off
    bool turn_on;       ///< switch the light on (\c true) of off (\c false)
};

/**
 * @brief The LightScheduler class
 */
class LightScheduler :
    public IScheduler
{
public:
    /**
     * @brief LightScheduler
     * @param timer
     * @param light_controller
     */
    LightScheduler (ITimeService & timer,
                    ISwitchControl & light_controller);

    /**
     * @brief ~LightScheduler
     */
    virtual ~LightScheduler ();

    /**
     * @copydoc IScheduler::wakeup
     */
    virtual void wakeup ();

    /**
     * @brief Set a schedule to turn on the light at a specific time of the day
     * @param schedule_time The schedule time of the day
     * @param light_id Id of the light to switch on
     */
    void schedule_turn_on (TimeOfDay schedule_time,
                           uint32_t light_id);

    /**
     * @brief Set a schedule to turn off the light at a specific time of the day
     * @param schedule_time The schedule time of the day
     * @param light_id Id of the light to switch off
     */
    void schedule_turn_off (TimeOfDay schedule_time,
                            uint32_t light_id);

private:
    void set_schedule (TimeOfDay schedule_time,
                       LightScheduleAction action);

    ITimeService & time_service_;
    ISwitchControl & light_controller_;
    std::multimap<TimeOfDay, LightScheduleAction, TimeCompare> schedules_;
};


} // namespace HomeAutomation



#endif //SCHEDULER_INTERFACE_H_
