#include <gtest/gtest.h>
#include <cucumber-cpp/autodetect.hpp>
#include <string>
#include <cstdint>

#include "home_automation_context.h"

#include "step_definition_helper_methods.h"

using cucumber::ScenarioScope;

using HomeAutomation::TimeOfDay;
using boost::gregorian::date;
using boost::gregorian::day_clock;
using boost::posix_time::hours;
using boost::posix_time::minutes;

namespace HomeAutomationFeatureTests
{

// -----------------------------------------------------------------------------
// Step Definitions

GIVEN ("^light (\\d+) is scheduled to turn \"(ON|OFF)\" at (\\d{2,2}):(\\d{2,2})$")
{
    REGEX_PARAM(uint32_t, light_no);
    REGEX_PARAM(std::string, light_state);
    REGEX_PARAM(int32_t, schedule_hour);
    REGEX_PARAM(int32_t, schedule_minute);

    ScenarioScope<HomeAutomationContext> context;

    const TimeOfDay schedule = {schedule_hour, schedule_minute};

    if (state_bool(light_state))
    {
        context->light_scheduler.schedule_turn_on(schedule, light_no);
    }
    else
    {
        context->light_scheduler.schedule_turn_off(schedule, light_no);
    }
}


GIVEN ("^the following schedules are set")
{
    TABLE_PARAM(schedule_params);
    ScenarioScope<HomeAutomationContext> context;
    const auto& schedules = schedule_params.hashes();
    for (const auto& schedule : schedules)
    {
        const TimeOfDay scheduled_time = TimeOfDay::from_string(schedule.at("schedule time"));

        const uint32_t light_no = fromString<uint32_t>(schedule.at("light"));
        const std::string light_state = std::string(schedule.at("state"));

        if (state_bool(light_state))
        {
            context->light_scheduler.schedule_turn_on(scheduled_time, light_no);
        }
        else
        {
            context->light_scheduler.schedule_turn_off(scheduled_time, light_no);
        }
    }
}


WHEN ("^the time turns (\\d{2,2}):(\\d{2,2})$")
{
    REGEX_PARAM(uint32_t, hour);
    REGEX_PARAM(uint32_t, minute);

    ScenarioScope<HomeAutomationContext> context;

    const date today(day_clock::local_day());
    const ptime current_time(today, hours(hour) + minutes(minute));

    context->timerService.set_current_time(current_time);
    context->timerService.wakeup_scheduler();
}


}