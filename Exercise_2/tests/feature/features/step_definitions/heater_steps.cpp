#include <gtest/gtest.h>
#include <cucumber-cpp/autodetect.hpp>
#include "home_automation_context.h"

#include "step_definition_helper_methods.h"

using cucumber::ScenarioScope;


namespace HomeAutomationFeatureTests
{

// -----------------------------------------------------------------------------
// Test Doubles

class FakeHeater :
    public HomeAutomation::IDigitalIO
{
public:
    FakeHeater () :
        value_(false)
    {
    }

    virtual void set (bool value)
    {
        value_ = value;
    }

    virtual bool get () const
    {
        return value_;
    }

private:
    bool value_;

};


GIVEN ("^the current temperature is (\\d+)°C$")
{
    REGEX_PARAM(uint32_t, current_temperature);
    ScenarioScope<HomeAutomationContext> context;

    context->temperatureSensor.set_temperature(current_temperature);
}


WHEN ("^I set the room temperature to (\\d+)°C$")
{
    REGEX_PARAM(uint32_t, temperature);
    ScenarioScope<HomeAutomationContext> context;
    context->home_controller.set_room_temperature(temperature);
}


THEN ("^the heater should be \"(ON|OFF)\"$")
{
    REGEX_PARAM(std::string, heater_state);
    const bool expected_heater_state = state_bool(heater_state);

    ScenarioScope<HomeAutomationContext> context;
    ASSERT_EQ(expected_heater_state, context->home_controller.heater_state());
}

}