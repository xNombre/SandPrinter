#pragma once

#include <vector>

#include <motor/Motor.hpp>
#include <config/DynamicConstants.hpp>
#include <config/Constants.hpp>
#include <gpio/FakeGpio.hpp>

class BrushController {
public:
    BrushController();
    ~BrushController() = default;

    // If async is true paint delay is moved to wait_for_motors()
    bool paint(uint8_t brush_number, uint8_t steps, bool async = false);
    void wait_for_motors(bool do_paint_delay = true);

private:
    std::vector<Motor<FakeGpio>> brushes;

    uint32_t paint_delay_ms;

    const std::vector<std::pair<DynamicConstants::Option, uint8_t>> brush_list = {
        {DynamicConstants::Option::BRUSH_1_COLOR, Constants::MOTOR_BRUSH1_GPIO},
        {DynamicConstants::Option::BRUSH_2_COLOR, Constants::MOTOR_BRUSH2_GPIO},
        {DynamicConstants::Option::BRUSH_3_COLOR, Constants::MOTOR_BRUSH3_GPIO},
        {DynamicConstants::Option::BRUSH_4_COLOR, Constants::MOTOR_BRUSH4_GPIO}
    };
};