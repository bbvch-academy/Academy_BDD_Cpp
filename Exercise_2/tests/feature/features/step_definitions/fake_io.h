#ifndef FAKE_IO_H_
#define FAKE_IO_H_

#include "digital_io_interface.h"

namespace HomeAutomationFeatureTests
{

class FakeIO :
    public HomeAutomation::IDigitalIO
{
public:
    FakeIO () :
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

}

#endif //FAKE_IO_H_

