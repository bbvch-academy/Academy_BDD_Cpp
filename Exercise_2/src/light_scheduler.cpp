#include <memory>
#include <sstream>
#include <stdexcept>

#include "light_scheduler.h"
#include "time_service_interface.h"
#include "switch_control_interface.h"

using boost::posix_time::minutes;
using boost::posix_time::ptime;
using boost::posix_time::time_duration;

namespace HomeAutomation
{


TimeOfDay TimeOfDay::from_string(std::string time_as_string)
{
  std::istringstream ss(time_as_string);
  const char delimiter = ':';
  std::string hour_part;
  std::getline(ss, hour_part, delimiter);

  if (ss.eof()) {
    std::stringstream message("Argument has wrong format.");
    message << " Is " << time_as_string << " but should have format 'hh:mm'.";
    throw std::invalid_argument(message.str());
  }

  const uint32_t size_of_hour_part = 2;
  uint32_t first_invalid_pos = 0;
  int32_t hour = std::stoi(hour_part, &first_invalid_pos);

  if (first_invalid_pos < size_of_hour_part) {
    std::stringstream message("Argument has wrong format.");
    message << " Is " << time_as_string << " but should have format 'hh:mm' with hh a valid two digit number";
    throw std::invalid_argument(message.str());
  }

  std::string minute_part;
  std::getline(ss, minute_part);

  const uint32_t size_of_minute_part = 2;
  first_invalid_pos = 0;
  int32_t minute = std::stoi(minute_part, &first_invalid_pos);

  if (first_invalid_pos < size_of_minute_part) {
    std::stringstream message("Argument has wrong format.");
    message << " Is " << time_as_string << " but should have format 'hh:mm' with mm a valid two digit number";
    throw std::invalid_argument(message.str());
  }

  TimeOfDay return_value = {hour, minute};
  return return_value;
}


LightScheduler::LightScheduler (ITimeService& timer,
                                ISwitchControl& light_controller):
  time_service_(timer),
  light_controller_(light_controller)
{

}


LightScheduler::~LightScheduler ()
{

}

void LightScheduler::wakeup ()
{
  ptime current_time = time_service_.get_curent_time();

  const time_duration current_time_of_day = current_time.time_of_day();

  const TimeOfDay schedule = {current_time_of_day.hours(), current_time_of_day.minutes()};

  auto schedule_iter_pair = schedules_.equal_range(schedule);

  for(auto iter = schedule_iter_pair.first; iter !=  schedule_iter_pair.second; ++iter )
  {
    const LightScheduleAction action = iter->second;
    if (action.turn_on) {
      light_controller_.switch_on(action.light_id);
    }
    else
    {
      light_controller_.switch_off(action.light_id);
    }
  }
}

void LightScheduler::schedule_turn_on (TimeOfDay schedule_time,
                                       uint32_t light_id)
{
  const bool turn_light_on = true;
  const LightScheduleAction action = {light_id, turn_light_on };

  set_schedule(schedule_time, action);
}

void LightScheduler::schedule_turn_off (TimeOfDay schedule_time,
                                        uint32_t light_id)
{
  const bool turn_light_off = false;
  const LightScheduleAction action = {light_id, turn_light_off };

  set_schedule(schedule_time, action);
}

void LightScheduler::set_schedule(TimeOfDay schedule_time,
                                  LightScheduleAction action)
{
  const long one_minute = 1;
  time_service_.set_periodic_alarm(minutes(one_minute), this);

  schedules_.insert(std::make_pair(schedule_time, action));
}




} // namespace HomeAutomation

