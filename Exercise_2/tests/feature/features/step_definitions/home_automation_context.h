#ifndef HOME_AUTOMATION_CONTEXT_H_
#define HOME_AUTOMATION_CONTEXT_H_

#include "fake_io.h"
#include "fake_temperature_sensor.h"
#include "fake_time_service.h"

#include "home_automation_control.h"
#include "light_controller.h"
#include "scheduler_interface.h"
#include "light_scheduler.h"
#include "heater_controller.h"

using HomeAutomation::HomeAutomationControl;
using HomeAutomation::HeaterController;
using HomeAutomation::ITemperatureSensor;
using HomeAutomation::LightController;
using HomeAutomation::LightScheduler;

namespace HomeAutomationFeatureTests
{

struct HomeAutomationContext
{

    HomeAutomationContext () :
        heater(),
        temperatureSensor(),
        timerService(),
        light_controller(),
        heater_controller(heater, temperatureSensor, timerService),
        home_controller(light_controller, heater_controller),
        light_scheduler(timerService, light_controller)
    {

    }

    FakeIO heater;
    FakeTemperatureSensor temperatureSensor;
    FakeTimeService timerService;
    LightController light_controller;
    HeaterController heater_controller;
    HomeAutomationControl home_controller;
    LightScheduler light_scheduler;

};

}

#endif //HOME_AUTOMATION_CONTEXT_H_
