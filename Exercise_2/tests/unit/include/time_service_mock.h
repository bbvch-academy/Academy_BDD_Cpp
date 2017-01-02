#ifndef TIME_SERVICE_MOCK_H_
#define TIME_SERVICE_MOCK_H_

#include <gmock/gmock.h>
#include "time_service_interface.h"

using boost::posix_time::ptime;
using boost::posix_time::time_duration;
using HomeAutomation::IScheduler;

namespace
{

/**
 * Time Service Mock
*/
class TimeServiceMock :
    public HomeAutomation::ITimeService
{
public:
    MOCK_CONST_METHOD0(get_curent_time, ptime());

    MOCK_METHOD2(set_periodic_alarm,
                 void (time_duration
                     duration,
                         IScheduler * scheduler));
};


} // namespace



#endif //TTIME_SERVICE_MOCK_H_

