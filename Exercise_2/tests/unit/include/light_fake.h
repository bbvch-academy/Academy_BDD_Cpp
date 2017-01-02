#ifndef LIGHT_FAKE_H
#define LIGHT_FAKE_H

#include <gmock/gmock.h>

#include "digital_io_interface.h"

namespace
{

/**
 * Light Fake implementation
*/
class LightFake :
    public HomeAutomation::IDigitalIO
{
public:
    LightFake () :
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

} // namespace

#endif //LIGHT_FAKE_H
