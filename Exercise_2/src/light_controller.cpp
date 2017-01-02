#include "light_controller.h"

namespace HomeAutomation
{

LightController::LightController ()
{
}

void LightController::add_light (const uint32_t id,
                                 std::shared_ptr<IDigitalIO> light)
{
    lights_.insert(std::make_pair(id, light));
}

void LightController::switch_on (uint32_t id)
{
    const bool on = true;
    lights_.at(id)->set(on);
}

void LightController::switch_off (uint32_t id)
{
    const bool off = false;
    lights_.at(id)->set(off);
}

bool LightController::switch_state (uint32_t id) const
{
    const auto light = lights_.at(id);
    return light->get();
}

}


