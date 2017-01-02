#ifndef LIGHT_CONTROLLER_H_
#define LIGHT_CONTROLLER_H_

#include <cstdint>
#include <map>
#include <memory>
#include "digital_io_interface.h"
#include "switch_control_interface.h"


namespace HomeAutomation
{

/**
 * @brief The LightController class
 */
class LightController :
    public ISwitchControl
{
public:
    /**
     * @brief LightController
     */
    LightController ();

    /**
     * @brief Add a new light to the controller
     * @param id an unique id identifying the light
     * @param light a light object
     */
    void add_light (const uint32_t id,
                    std::shared_ptr<IDigitalIO> light);

    /**
     * @copydoc ISwitchControl::switch_on
     */
    virtual void switch_on (uint32_t id);

    /**
     * @copydoc ISwitchControl::switch_off
     */
    virtual void switch_off (uint32_t id);

    /**
     * @copydoc ISwitchControl::switch_state
     */
    virtual bool switch_state (uint32_t id) const;

private:
    std::map<uint32_t, std::shared_ptr<IDigitalIO> > lights_;
};


} // namespace HomeAutomation

#endif //LIGHT_CONTROLLER_H_
