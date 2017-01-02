#ifndef TIME_SERVICE_INTERFACE_H_
#define TIME_SERVICE_INTERFACE_H_

#include <memory>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>

#include "scheduler_interface.h"

using boost::posix_time::ptime;
using boost::posix_time::time_duration;

namespace HomeAutomation
{

/**
  * @brief Interface for a time service
  */
class ITimeService
{
public:
    /**
     * @brief ~ITimeService
     */
    virtual ~ITimeService ()
    {}

    /**
     * @brief Get the current time and date
     * @return the current time and date
     */
    virtual ptime get_curent_time () const = 0;

    /**
     * @brief Set a periodic alarm
     * @param duration Duration of the period
     * @param scheduler The scheduler to wakeup periodicaly
     */
    virtual void set_periodic_alarm (time_duration duration, IScheduler * scheduler) = 0;

protected:
    /**
     * Assignment of abstract type is not allowed
    */
    ITimeService & operator= (const ITimeService &);
};


} // namespace HomeAutomation



#endif //TIME_SERVICE_INTERFACE_H_
