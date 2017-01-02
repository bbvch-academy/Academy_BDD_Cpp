#include <cstdint>
#include <stdexcept>
#include <gtest/gtest.h>
#include "light_scheduler.h"
#include "time_service_mock.h"
#include "light_controller_mock.h"


namespace
{

using HomeAutomation::LightScheduler;
using HomeAutomation::TimeOfDay;

using boost::posix_time::time_duration;
using boost::posix_time::ptime;
using boost::posix_time::hours;
using boost::posix_time::minutes;
using boost::gregorian::day_clock;

using ::testing::Eq;
using ::testing::Ref;
using ::testing::_;
using ::testing::Return;


TEST(LightSchedulerTest, setting_a_ON_schedule_sets_a_timer_period_of_one_minute_length_and_itself_as_observer)
{
    TimeServiceMock timer_service;
    LightControllerMock light_controller;

    LightScheduler testee(timer_service, light_controller);

    const time_duration one_minute_period(minutes(1));

    EXPECT_CALL(timer_service, set_periodic_alarm(Eq(one_minute_period), &testee));

    const int32_t schedule_hours = 9;
    const int32_t schedule_minutes = 30;
    const TimeOfDay schedule = {schedule_hours, schedule_minutes};

    const uint32_t light_id = 1;

    testee.schedule_turn_on(schedule, light_id);
}

TEST(LightSchedulerTest, setting_a_OFF_schedule_sets_a_timer_period_of_one_minute_length_and_itself_as_observer)
{
    TimeServiceMock timer_service;
    LightControllerMock light_controller;

    LightScheduler testee(timer_service, light_controller);

    const time_duration one_minute_period(minutes(1));

    EXPECT_CALL(timer_service, set_periodic_alarm(Eq(one_minute_period), &testee));

    const int32_t schedule_hours = 9;
    const int32_t schedule_minutes = 30;
    const TimeOfDay schedule = {schedule_hours, schedule_minutes};

    const uint32_t light_id = 1;

    testee.schedule_turn_off(schedule, light_id);
}


TEST(LightSchedulerTest, check_current_time_upon_wakeup)
{

    ::testing::NiceMock<TimeServiceMock> timer_service;
    ::testing::NiceMock<LightControllerMock> light_controller;

    LightScheduler testee(timer_service, light_controller);

    ON_CALL(timer_service, set_periodic_alarm(_, _))
        .WillByDefault(Return());

    const int32_t schedule_hours = 9;
    const int32_t schedule_minutes = 30;
    const TimeOfDay schedule = {schedule_hours, schedule_minutes};

    const uint32_t light_id = 1;

    const hours current_hour = hours(schedule_hours);
    const minutes current_minute = minutes(schedule_minutes);

    const ptime current_time(day_clock::local_day(), current_hour + current_minute);

    EXPECT_CALL(timer_service, get_curent_time())
        .WillOnce(Return(current_time));

    testee.schedule_turn_on(schedule, light_id);

    testee.wakeup();
}

TEST(LightSchedulerTest, upon_wakeup_turn_light_on_when_a_turn_on_schedule_is_equal_to_the_current_time)
{

    ::testing::NiceMock<TimeServiceMock> timer_service;
    LightControllerMock light_controller;

    LightScheduler testee(timer_service, light_controller);

    ON_CALL(timer_service, set_periodic_alarm(_, _))
        .WillByDefault(Return());

    const int32_t schedule_hours = 9;
    const int32_t schedule_minutes = 30;
    const TimeOfDay schedule = {schedule_hours, schedule_minutes};

    const uint32_t light_id = 1;

    const hours current_hour = hours(schedule_hours);
    const minutes current_minute = minutes(schedule_minutes);

    const ptime current_time(day_clock::local_day(), current_hour + current_minute);

    EXPECT_CALL(timer_service, get_curent_time())
        .WillOnce(Return(current_time));

    EXPECT_CALL(light_controller, switch_on(light_id));

    testee.schedule_turn_on(schedule, light_id);

    testee.wakeup();
}

TEST(LightSchedulerTest, upon_wakeup_do_not_turn_light_on_when_the_current_time_is_one_hour_before_the_turn_on_schedule)
{

    ::testing::NiceMock<TimeServiceMock> timer_service;
    LightControllerMock light_controller;

    LightScheduler testee(timer_service, light_controller);

    ON_CALL(timer_service, set_periodic_alarm(_, _))
        .WillByDefault(Return());

    const int32_t schedule_hours = 9;
    const int32_t schedule_minutes = 30;
    const TimeOfDay schedule = {schedule_hours, schedule_minutes};

    const uint32_t light_id = 1;

    const hours current_hour = hours(schedule_hours - 1);
    const minutes current_minute = minutes(schedule_minutes);

    const ptime current_time(day_clock::local_day(), current_hour + current_minute);

    EXPECT_CALL(timer_service, get_curent_time())
        .WillOnce(Return(current_time));

    EXPECT_CALL(light_controller, switch_on(light_id))
        .Times(0);

    testee.schedule_turn_on(schedule, light_id);

    testee.wakeup();
}

TEST(LightSchedulerTest, upon_wakeup_do_not_turn_light_on_when_the_current_time_is_one_hour_after_the_turn_on_schedule)
{

    ::testing::NiceMock<TimeServiceMock> timer_service;
    LightControllerMock light_controller;

    LightScheduler testee(timer_service, light_controller);

    ON_CALL(timer_service, set_periodic_alarm(_, _))
        .WillByDefault(Return());

    const int32_t schedule_hours = 9;
    const int32_t schedule_minutes = 30;
    const TimeOfDay schedule = {schedule_hours, schedule_minutes};

    const uint32_t light_id = 1;

    const hours current_hour = hours(schedule_hours + 1);
    const minutes current_minute = minutes(schedule_minutes);

    const ptime current_time(day_clock::local_day(), current_hour + current_minute);

    EXPECT_CALL(timer_service, get_curent_time())
        .WillOnce(Return(current_time));

    EXPECT_CALL(light_controller, switch_on(light_id))
        .Times(0);

    testee.schedule_turn_on(schedule, light_id);

    testee.wakeup();
}

TEST(LightSchedulerTest,
     upon_wakeup_do_not_turn_light_on_when_the_current_time_is_one_minute_before_the_turn_on_schedule)
{

    ::testing::NiceMock<TimeServiceMock> timer_service;
    LightControllerMock light_controller;

    LightScheduler testee(timer_service, light_controller);

    ON_CALL(timer_service, set_periodic_alarm(_, _))
        .WillByDefault(Return());

    const int32_t schedule_hours = 9;
    const int32_t schedule_minutes = 30;
    const TimeOfDay schedule = {schedule_hours, schedule_minutes};

    const uint32_t light_id = 1;

    const hours current_hour = hours(schedule_hours);
    const minutes current_minute = minutes(schedule_minutes - 1);

    const ptime current_time(day_clock::local_day(), current_hour + current_minute);

    EXPECT_CALL(timer_service, get_curent_time())
        .WillOnce(Return(current_time));

    EXPECT_CALL(light_controller, switch_on(light_id))
        .Times(0);

    testee.schedule_turn_on(schedule, light_id);

    testee.wakeup();
}

TEST(LightSchedulerTest,
     upon_wakeup_do_not_turn_light_on_when_the_current_time_is_one_minute_after_the_turn_on_schedule)
{

    ::testing::NiceMock<TimeServiceMock> timer_service;
    LightControllerMock light_controller;

    LightScheduler testee(timer_service, light_controller);

    ON_CALL(timer_service, set_periodic_alarm(_, _))
        .WillByDefault(Return());

    const int32_t schedule_hours = 9;
    const int32_t schedule_minutes = 30;
    const TimeOfDay schedule = {schedule_hours, schedule_minutes};

    const uint32_t light_id = 1;

    const hours current_hour = hours(schedule_hours);
    const minutes current_minute = minutes(schedule_minutes + 1);

    const ptime current_time(day_clock::local_day(), current_hour + current_minute);

    EXPECT_CALL(timer_service, get_curent_time())
        .WillOnce(Return(current_time));

    EXPECT_CALL(light_controller, switch_on(light_id))
        .Times(0);

    testee.schedule_turn_on(schedule, light_id);

    testee.wakeup();
}

TEST(LightSchedulerTest, upon_wakeup_turn_light_off_when_a_turn_off_schedule_is_equal_to_the_current_time)
{

    ::testing::NiceMock<TimeServiceMock> timer_service;
    LightControllerMock light_controller;

    LightScheduler testee(timer_service, light_controller);

    ON_CALL(timer_service, set_periodic_alarm(_, _))
        .WillByDefault(Return());

    const int32_t schedule_hours = 9;
    const int32_t schedule_minutes = 30;
    const TimeOfDay schedule = {schedule_hours, schedule_minutes};

    const uint32_t light_id = 1;

    const hours current_hour = hours(schedule_hours);
    const minutes current_minute = minutes(schedule_minutes);

    const ptime current_time(day_clock::local_day(), current_hour + current_minute);

    EXPECT_CALL(timer_service, get_curent_time())
        .WillOnce(Return(current_time));

    EXPECT_CALL(light_controller, switch_off(light_id));

    testee.schedule_turn_off(schedule, light_id);

    testee.wakeup();
}

TEST(LightSchedulerTest,
     upon_wakeup_do_not_turn_light_off_when_the_current_time_is_one_hour_before_the_turn_off_schedule)
{

    ::testing::NiceMock<TimeServiceMock> timer_service;
    LightControllerMock light_controller;

    LightScheduler testee(timer_service, light_controller);

    ON_CALL(timer_service, set_periodic_alarm(_, _))
        .WillByDefault(Return());

    const int32_t schedule_hours = 9;
    const int32_t schedule_minutes = 30;
    const TimeOfDay schedule = {schedule_hours, schedule_minutes};

    const uint32_t light_id = 1;

    const hours current_hour = hours(schedule_hours - 1);
    const minutes current_minute = minutes(schedule_minutes);

    const ptime current_time(day_clock::local_day(), current_hour + current_minute);

    EXPECT_CALL(timer_service, get_curent_time())
        .WillOnce(Return(current_time));

    EXPECT_CALL(light_controller, switch_off(light_id))
        .Times(0);

    testee.schedule_turn_off(schedule, light_id);

    testee.wakeup();
}

TEST(LightSchedulerTest,
     upon_wakeup_do_not_turn_light_off_when_the_current_time_is_one_hour_after_the_turn_off_schedule)
{

    ::testing::NiceMock<TimeServiceMock> timer_service;
    LightControllerMock light_controller;

    LightScheduler testee(timer_service, light_controller);

    ON_CALL(timer_service, set_periodic_alarm(_, _))
        .WillByDefault(Return());

    const int32_t schedule_hours = 9;
    const int32_t schedule_minutes = 30;
    const TimeOfDay schedule = {schedule_hours, schedule_minutes};

    const uint32_t light_id = 1;

    const hours current_hour = hours(schedule_hours + 1);
    const minutes current_minute = minutes(schedule_minutes);

    const ptime current_time(day_clock::local_day(), current_hour + current_minute);

    EXPECT_CALL(timer_service, get_curent_time())
        .WillOnce(Return(current_time));

    EXPECT_CALL(light_controller, switch_off(light_id))
        .Times(0);

    testee.schedule_turn_off(schedule, light_id);

    testee.wakeup();
}

TEST(LightSchedulerTest,
     upon_wakeup_do_not_turn_light_off_when_the_current_time_is_one_minute_before_the_turn_off_schedule)
{

    ::testing::NiceMock<TimeServiceMock> timer_service;
    LightControllerMock light_controller;

    LightScheduler testee(timer_service, light_controller);

    ON_CALL(timer_service, set_periodic_alarm(_, _))
        .WillByDefault(Return());

    const int32_t schedule_hours = 9;
    const int32_t schedule_minutes = 30;
    const TimeOfDay schedule = {schedule_hours, schedule_minutes};

    const uint32_t light_id = 1;

    const hours current_hour = hours(schedule_hours);
    const minutes current_minute = minutes(schedule_minutes - 1);

    const ptime current_time(day_clock::local_day(), current_hour + current_minute);

    EXPECT_CALL(timer_service, get_curent_time())
        .WillOnce(Return(current_time));

    EXPECT_CALL(light_controller, switch_off(light_id))
        .Times(0);

    testee.schedule_turn_off(schedule, light_id);

    testee.wakeup();
}

TEST(LightSchedulerTest,
     upon_wakeup_do_not_turn_light_off_when_the_current_time_is_one_minute_after_the_turn_off_schedule)
{

    ::testing::NiceMock<TimeServiceMock> timer_service;
    LightControllerMock light_controller;

    LightScheduler testee(timer_service, light_controller);

    ON_CALL(timer_service, set_periodic_alarm(_, _))
        .WillByDefault(Return());

    const int32_t schedule_hours = 9;
    const int32_t schedule_minutes = 30;
    const TimeOfDay schedule = {schedule_hours, schedule_minutes};

    const uint32_t light_id = 1;

    const hours current_hour = hours(schedule_hours);
    const minutes current_minute = minutes(schedule_minutes + 1);

    const ptime current_time(day_clock::local_day(), current_hour + current_minute);

    EXPECT_CALL(timer_service, get_curent_time())
        .WillOnce(Return(current_time));

    EXPECT_CALL(light_controller, switch_off(light_id))
        .Times(0);

    testee.schedule_turn_off(schedule, light_id);

    testee.wakeup();
}

TEST(LightSchedulerTest, both_lights_are_turnd_on_if_two_lights_are_scheduled_for_the_same_time)
{
    ::testing::NiceMock<TimeServiceMock> timer_service;
    LightControllerMock light_controller;

    LightScheduler testee(timer_service, light_controller);

    ON_CALL(timer_service, set_periodic_alarm(_, _))
        .WillByDefault(Return());

    const int32_t schedule_hours = 9;
    const int32_t schedule_minutes = 30;
    const TimeOfDay schedule = {schedule_hours, schedule_minutes};

    const uint32_t first_light_id = 1;
    const uint32_t second_light_id = 3;

    const hours current_hour = hours(schedule_hours);
    const minutes current_minute = minutes(schedule_minutes);

    const ptime current_time(day_clock::local_day(), current_hour + current_minute);

    EXPECT_CALL(timer_service, get_curent_time())
        .WillOnce(Return(current_time));

    EXPECT_CALL(light_controller, switch_on(first_light_id));
    EXPECT_CALL(light_controller, switch_on(second_light_id));

    testee.schedule_turn_on(schedule, first_light_id);
    testee.schedule_turn_on(schedule, second_light_id);

    testee.wakeup();
}

TEST(TimeOfDay, from_string_creates_a_TimeOfDay_object_from_valid_time_string)
{
    TimeOfDay time_of_day_sedule = TimeOfDay::from_string("09:00");
    ASSERT_EQ(9, time_of_day_sedule.hour);
    ASSERT_EQ(0, time_of_day_sedule.minute);
}

TEST(TimeOfDay, from_string_throws_exception_if_no_delimiter)
{
    ASSERT_THROW(TimeOfDay::from_string("0900"), std::invalid_argument);
}

TEST(TimeOfDay, from_string_throws_exception_if_wrong_delimiter)
{
    ASSERT_THROW(TimeOfDay::from_string("09,00"), std::invalid_argument);
}

TEST(TimeOfDay, from_string_throws_exception_if_hour_part_not_a_number)
{
    ASSERT_THROW(TimeOfDay::from_string("0A:00"), std::invalid_argument);
}

TEST(TimeOfDay, from_string_throws_exception_if_minute_part_not_a_number)
{
    ASSERT_THROW(TimeOfDay::from_string("00:A0"), std::invalid_argument);
}

} //namespace

