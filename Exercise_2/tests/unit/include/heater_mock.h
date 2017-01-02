#ifndef HEATER_MOCK_H
#define HEATER_MOCK_H

#include <gmock/gmock.h>

#include "digital_io_interface.h"

namespace
{

class HeaterMock :
    public HomeAutomation::IDigitalIO
{
public:
    MOCK_METHOD1(set, void(bool
        value));

    MOCK_CONST_METHOD0(get, bool());
};

} // namespace

#endif //HEATER_MOCK_H
