#ifndef FAKE_TIME_SERVICE_H_
#define FAKE_TIME_SERVICE_H_

#include "time_service_interface.h"

namespace HomeAutomationFeatureTests
{

/**
*  A Fake implementation of a timer used for feature scenarios
*/
class FakeTimeService :
    public HomeAutomation::ITimeService
{
public:
    FakeTimeService () :
        current_date_(),
        scheduler_(nullptr)
    {
    }

    /**
     * Set the current time the timer should return
    */
    void set_current_time (ptime current_date)
    {
        current_date_ = current_date;
    }

    /**
     * @copydoc ITimeService::get_curent_time
     */
    virtual ptime get_curent_time () const
    {
        return current_date_;
    }

    /**
     * @copydoc ITimeService::set_periodic_alarm
     */
    virtual void set_periodic_alarm (time_duration /*duration*/, HomeAutomation::IScheduler * scheduler)
    {
        scheduler_ = scheduler;
    }

    /**
    * Trigger the wakeup call
    */
    void wakeup_scheduler ()
    {
        if (scheduler_)
        {
            scheduler_->wakeup();
        }

    }

private:
    ptime current_date_;
    HomeAutomation::IScheduler * scheduler_;
};


}

#endif //FAKE_TIME_SERVICE_H_
