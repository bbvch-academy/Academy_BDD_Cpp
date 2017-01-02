#ifndef LIGHT_CONTROL_MOCK_H
#define LIGHT_CONTROL_MOCK_H

#include <cstdint>
#include <gmock/gmock.h>
#include "switch_control_interface.h"

namespace
{

/**
 * Light Controller Mock
*/
class LightControllerMock :
    public HomeAutomation::ISwitchControl
{
public:

    MOCK_METHOD1(switch_on, void (uint32_t
        id));
    MOCK_METHOD1(switch_off, void (uint32_t
        id));
    MOCK_CONST_METHOD1(switch_state, bool (uint32_t
        id));
};

} // namespace

#endif //LIGHT_CONTROLLER_MOCK_H
