#ifndef STEP_DEFINITION_HELPER_METHODS_H_
#define STEP_DEFINITION_HELPER_METHODS_H_

#include <string>

namespace HomeAutomationFeatureTests
{


// -----------------------------------------------------------------------------
// Helper methods

static bool state_bool (std::string state_as_string)
{
    bool state = false;
    if (state_as_string.find("ON") != std::string::npos)
    {
        state = true;
    }
    else
    {
        state = false;
    }
    return state;
}

template<typename T>
T fromString (const std::string & s)
{
    std::istringstream stream(s);
    T t;
    stream >> t;
    if (stream.fail())
    {
        throw std::invalid_argument("Cannot convert parameter");
    }
    return t;
}


}
#endif //STEP_DEFINITION_HELPER_METHODS_H_
