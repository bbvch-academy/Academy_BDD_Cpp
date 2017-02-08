#include <gtest/gtest.h>
#include <cucumber-cpp/autodetect.hpp>
#include <string>
#include <cstdint>

#include "home_automation_context.h"

#include "step_definition_helper_methods.h"

using cucumber::ScenarioScope;

namespace HomeAutomationFeatureTests
{

// -----------------------------------------------------------------------------
// Step Definitions

GIVEN ("^the light (\\d+) is \"(ON|OFF)\"$")
{
    REGEX_PARAM(uint32_t, light_no);
    REGEX_PARAM(std::string, light_state);
    const bool expected_light_state = state_bool(light_state);

    ScenarioScope<HomeAutomationContext> context;

    context->light_controller.add_light(light_no, std::make_shared<FakeIO>());

    context->home_controller.switch_light(light_no, expected_light_state);

    ASSERT_EQ(expected_light_state, context->home_controller.light_state(light_no));
}

GIVEN ("^the following lights have state")
{
    TABLE_PARAM(light_params);
    ScenarioScope<HomeAutomationContext> context;
    const auto & lights = light_params.hashes();
    for (const auto& light : lights)
    {
        const uint32_t light_no = fromString<uint32_t>(light.at("light"));
        const std::string light_state = std::string(light.at("state"));

        context->light_controller.add_light(light_no, std::make_shared<FakeIO>());

        const bool expected_light_state = state_bool(light_state);
        context->home_controller.switch_light(light_no, expected_light_state);

        ASSERT_EQ(expected_light_state, context->home_controller.light_state(light_no));
    }
}

WHEN ("^I switch the light (\\d+) \"(ON|OFF)\"$")
{
    REGEX_PARAM(uint32_t, light_no);
    REGEX_PARAM(std::string, light_state);
    ScenarioScope<HomeAutomationContext> context;
    context->home_controller.switch_light(light_no, state_bool(light_state));
}

THEN ("^the light (\\d+) should be \"(ON|OFF)\"$")
{
    REGEX_PARAM(uint32_t, light_no);
    REGEX_PARAM(std::string, light_state);
    const bool expected_light_state = state_bool(light_state);
    ScenarioScope<HomeAutomationContext> context;
    ASSERT_EQ(expected_light_state, context->home_controller.light_state(light_no));
}


THEN ("^the lights should have the following states")
{
    ScenarioScope<HomeAutomationContext> context;
    TABLE_PARAM(light_params);
    const auto & lights = light_params.hashes();
    for (const auto& light : lights)
    {
        const uint32_t light_no = fromString<uint32_t>(light.at("light"));
        const std::string light_state = std::string(light.at("state"));

        const bool expected_light_state = state_bool(light_state);
        ASSERT_EQ(expected_light_state, context->home_controller.light_state(light_no));
    }
}

}