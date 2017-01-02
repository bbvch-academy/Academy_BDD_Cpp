#include <string>
#include <stdexcept>
#include <gtest/gtest.h>

#include "light_mock.h"
#include "light_fake.h"
#include "light_controller.h"


using HomeAutomation::IDigitalIO;

namespace
{

TEST(LightControllerTest, an_added_light_can_be_switched_on)
{
    std::shared_ptr<LightMock> light(new LightMock());
    const bool light_on = true;

    EXPECT_CALL(*light, set(light_on));

    HomeAutomation::LightController testee;

    const uint32_t light_id = 1;
    testee.add_light(light_id, light);

    testee.switch_on(light_id);
}

TEST(LightControllerTest, an_added_light_can_be_switched_off)
{
    std::shared_ptr<LightMock> light(new LightMock());
    const bool light_off = false;

    EXPECT_CALL(*light, set(light_off));

    HomeAutomation::LightController testee;

    const uint32_t light_id = 1;
    testee.add_light(light_id, light);

    testee.switch_off(light_id);
}

TEST(LightControllerTest, a_light_switched_on_is_on)
{
    std::shared_ptr<LightFake> light(new LightFake());

    HomeAutomation::LightController testee;

    const uint32_t light_id = 1;
    testee.add_light(light_id, light);

    testee.switch_on(light_id);

    ASSERT_TRUE(testee.switch_state(light_id));
}

TEST(LightControllerTest, a_light_can_be_switched_on_and_off)
{
    std::shared_ptr<LightFake> light(new LightFake());

    HomeAutomation::LightController testee;

    const uint32_t light_id = 1;
    testee.add_light(light_id, light);

    testee.switch_on(light_id);

    ASSERT_TRUE(testee.switch_state(light_id));

    testee.switch_off(light_id);

    ASSERT_FALSE(testee.switch_state(light_id));
}

TEST(LightControllerTest, switching_an_unknown_light_on_throws_an_exception)
{
    std::shared_ptr<LightFake> light(new LightFake());

    HomeAutomation::LightController testee;

    const uint32_t light_id = 1;
    testee.add_light(light_id, light);

    const uint32_t unknown_light_id = 2;

    ASSERT_THROW(testee.switch_on(unknown_light_id), std::out_of_range);
}

TEST(LightControllerTest, switching_an_unknown_light_off_throws_an_exception)
{
    std::shared_ptr<LightFake> light(new LightFake());

    HomeAutomation::LightController testee;

    const uint32_t light_id = 1;
    testee.add_light(light_id, light);

    const uint32_t unknown_light_id = 2;

    ASSERT_THROW(testee.switch_off(unknown_light_id), std::out_of_range);
}


TEST(LightControllerTest, getting_the_state_of_an_unknown_light_throws_an_exception)
{
    std::shared_ptr<LightFake> light(new LightFake());

    HomeAutomation::LightController testee;

    const uint32_t light_id = 1;
    testee.add_light(light_id, light);

    const uint32_t unknown_light_id = 2;

    ASSERT_THROW(testee.switch_state(unknown_light_id), std::out_of_range);
}


} //namespace
