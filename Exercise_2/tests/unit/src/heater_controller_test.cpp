#include <gtest/gtest.h>
#include <cstdint>


#include "heater_controller.h"

#include "temperature_sensor_mock.h"
#include "time_service_mock.h"
#include "heater_mock.h"

using HomeAutomation::HeaterController;

using ::testing::Return;

namespace
{

TEST(HeaterControllerTest, getting_the_current_temperature_calls_the_temperature_sensor)
{
    ::testing::NiceMock<TemperatureSensorMock> temperature_sensor;
    ::testing::NiceMock<TimeServiceMock> time_service;
    ::testing::NiceMock<HeaterMock> heater;

    HeaterController testee(heater, temperature_sensor, time_service);

    const uint32_t temperature = 20;

    EXPECT_CALL(temperature_sensor, get_temperature())
        .WillOnce(Return(temperature));

    ASSERT_EQ(temperature, testee.get_current_temperature());
}

TEST(HeaterControllerTest, setting_a_target_temperature_higher_than_current_temperature_switchs_heater_on)
{
    ::testing::NiceMock<TemperatureSensorMock> temperature_sensor;
    ::testing::NiceMock<TimeServiceMock> time_service;
    ::testing::NiceMock<HeaterMock> heater;

    HeaterController testee(heater, temperature_sensor, time_service);

    const uint32_t current_temperature = 20;
    const bool switch_heater_on = true;

    ON_CALL(temperature_sensor, get_temperature())
        .WillByDefault(Return(current_temperature));

    ON_CALL(heater, get())
        .WillByDefault(Return(switch_heater_on));

    EXPECT_CALL(heater, set(switch_heater_on))
        .Times(1);

    const uint32_t target_temperature = current_temperature + 5;
    testee.set_target_temperature(target_temperature);

    ASSERT_TRUE(testee.get_heater_state());
}

TEST(HeaterControllerTest, setting_a_target_temperature_lower_than_current_temperature_switchs_heater_off)
{
    ::testing::NiceMock<TemperatureSensorMock> temperature_sensor;
    ::testing::NiceMock<TimeServiceMock> time_service;
    ::testing::NiceMock<HeaterMock> heater;

    HeaterController testee(heater, temperature_sensor, time_service);

    const uint32_t current_temperature = 20;
    const bool switch_heater_off = false;

    ON_CALL(temperature_sensor, get_temperature())
        .WillByDefault(Return(current_temperature));

    ON_CALL(heater, get())
        .WillByDefault(Return(switch_heater_off));

    EXPECT_CALL(heater, set(switch_heater_off))
        .Times(1);

    const uint32_t target_temperature = current_temperature - 5;
    testee.set_target_temperature(target_temperature);

    ASSERT_FALSE(testee.get_heater_state());
}

TEST(HeaterControllerTest, setting_a_target_temperature_higher_than_current_temperature_sets_a_timer)
{
    ::testing::NiceMock<TemperatureSensorMock> temperature_sensor;
    ::testing::NiceMock<TimeServiceMock> time_service;
    ::testing::NiceMock<HeaterMock> heater;

    HeaterController testee(heater, temperature_sensor, time_service);

    const uint32_t current_temperature = 20;

    ON_CALL(temperature_sensor, get_temperature())
        .WillByDefault(Return(current_temperature));

    EXPECT_CALL(time_service, set_periodic_alarm(::testing::_, ::testing::_))
        .Times(1);

    const uint32_t target_temperature = current_temperature + 5;
    testee.set_target_temperature(target_temperature);
}

TEST(HeaterControllerTest, setting_a_target_temperature_same_as_current_temperature_sets_a_timer)
{
    ::testing::NiceMock<TemperatureSensorMock> temperature_sensor;
    ::testing::NiceMock<TimeServiceMock> time_service;
    ::testing::NiceMock<HeaterMock> heater;

    HeaterController testee(heater, temperature_sensor, time_service);

    const uint32_t current_temperature = 20;

    ON_CALL(temperature_sensor, get_temperature())
        .WillByDefault(Return(current_temperature));

    EXPECT_CALL(time_service, set_periodic_alarm(::testing::_, ::testing::_))
        .Times(1);

    const uint32_t target_temperature = current_temperature;
    testee.set_target_temperature(target_temperature);
}

TEST(HeaterControllerTest, setting_a_target_temperature_lower_than_current_temperature_sets_a_timer)
{
    ::testing::NiceMock<TemperatureSensorMock> temperature_sensor;
    ::testing::NiceMock<TimeServiceMock> time_service;
    ::testing::NiceMock<HeaterMock> heater;

    HeaterController testee(heater, temperature_sensor, time_service);

    const uint32_t current_temperature = 20;

    ON_CALL(temperature_sensor, get_temperature())
        .WillByDefault(Return(current_temperature));

    EXPECT_CALL(time_service, set_periodic_alarm(::testing::_, ::testing::_))
        .Times(1);

    const uint32_t target_temperature = current_temperature - 5;
    testee.set_target_temperature(target_temperature);
}

TEST(HeaterControllerTest, switch_heater_on_upon_wakeup_if_current_temperature_is_lower_than_target_temperature)
{
    ::testing::NiceMock<TemperatureSensorMock> temperature_sensor;
    ::testing::NiceMock<TimeServiceMock> time_service;
    ::testing::NiceMock<HeaterMock> heater;

    HeaterController testee(heater, temperature_sensor, time_service);

    const uint32_t current_temperature = 20;
    const uint32_t target_temperature = current_temperature + 5;

    // we set target temperature before we set any expectations on the mock
    // to avoid triggering due to the set_target_temperature calls
    testee.set_target_temperature(target_temperature);

    EXPECT_CALL(temperature_sensor, get_temperature())
        .WillOnce(Return(current_temperature));

    const bool switch_heater_on = true;

    EXPECT_CALL(heater, set(switch_heater_on))
        .Times(1);

    testee.wakeup();
}


} //namespace
