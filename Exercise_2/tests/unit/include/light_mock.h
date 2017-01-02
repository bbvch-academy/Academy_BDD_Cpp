#ifndef LIGHT_MOCK_H
#define LIGHT_MOCK_H

#include <gmock/gmock.h>

#include "digital_io_interface.h"

namespace
{

/**
 * Light Mock
*/
class LightMock :
    public HomeAutomation::IDigitalIO
{
public:
    MOCK_METHOD1(set, void(bool
        value));

    MOCK_CONST_METHOD0(get, bool());
};

} // namespace

#endif //LIGHT_MOCK_H
