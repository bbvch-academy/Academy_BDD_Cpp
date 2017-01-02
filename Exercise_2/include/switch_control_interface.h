#ifndef SWITCH_CONTROL_INTERFACE_H_
#define SWITCH_CONTROL_INTERFACE_H_

#include <cstdint>

namespace HomeAutomation
{

/**
 * @brief Interface for a light controller
 */
class ISwitchControl
{
public:
    /**
     * @brief ~ISwitchControl
     */
    virtual ~ISwitchControl ()
    {}

    /**
     * @brief Switch a light on
     * @param id Id of the light to switch on
     */
    virtual void switch_on (uint32_t id) = 0;

    /**
     * @brief Switch a light off
     * @param id Id of the light to switch off
     */
    virtual void switch_off (uint32_t id) = 0;

    /**
     * @brief Get the current light state
     * @param id Id of the light
     * @retval true light is on
     * @retval false light is off
     */
    virtual bool switch_state (uint32_t id) const = 0;

protected:
    /**
     * Assignment of abstract type is not allowed
    */
    ISwitchControl & operator= (const ISwitchControl &);
};


} // namespace HomeAutomation

#endif //SWITCH_CONTROL_INTERFACE_H_
