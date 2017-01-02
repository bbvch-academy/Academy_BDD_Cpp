#include <gtest/gtest.h>
#include <map>
#include <cstdint>

#include "home_automation_control.h"
#include "switch_control_interface.h"
#include "temperature_control_interface.h"

namespace
{

class LightControlllerFake :
    public HomeAutomation::ISwitchControl
{
public:
    virtual ~LightControlllerFake ()
    {}

    virtual void switch_on (uint32_t id)
    {
        light_[id] = true;
    }


    virtual void switch_off (uint32_t id)
    {
        light_[id] = false;
    }

    virtual bool switch_state (uint32_t id) const
    {
        return light_.at(id);
    }

private:
    std::map<uint32_t, bool> light_;
};

class HeaterControllerFake :
    public HomeAutomation::ITemperatureControl
{
public:
    HeaterControllerFake () :
        temperature_(0),
        target_temperature_(0)
    {

    }

    void set_target_temperature (uint32_t temperature)
    {
        target_temperature_ = temperature;
    }

    void set_current_temperature (uint32_t temperature)
    {
        temperature_ = temperature;
    }

    virtual uint32_t get_current_temperature () const
    {
        return temperature_;
    }

    virtual bool get_heater_state () const
    {
        return (temperature_ < target_temperature_);
    }

private:
    uint32_t temperature_;
    uint32_t target_temperature_;
};


TEST(HomeAutomationControlTest, light_is_on_after_switching_light_on)
{
    LightControlllerFake light_controller;
    HeaterControllerFake heater_controller;

    HomeAutomation::HomeAutomationControl testee(light_controller, heater_controller);

    const uint32_t light_id = 2;
    const bool light_on = true;

    testee.switch_light(light_id, light_on);

    ASSERT_TRUE(testee.light_state(light_id));
}

TEST(HomeAutomationControlTest, light_is_off_after_switching_light_off)
{
    LightControlllerFake light_controller;
    HeaterControllerFake heater_controller;

    HomeAutomation::HomeAutomationControl testee(light_controller, heater_controller);

    const uint32_t light_id = 2;
    const bool light_off = false;

    testee.switch_light(light_id, light_off);

    ASSERT_FALSE(testee.light_state(light_id));
}

} //namespace
