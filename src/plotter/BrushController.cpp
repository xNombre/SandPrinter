#include "BrushController.hpp"

#include "pico/time.h"

#include "../gpio/Gpio.hpp"

BrushController::BrushController()
{
    auto dynamic_config = DynamicConstants::get_instance();

    paint_delay_ms = dynamic_config->get_value_int(DynamicConstants::Option::PAINT_DELAY).value();

    for (const auto& brush_entry : brush_list) {
        if (!dynamic_config->value_is_available(brush_entry.first))
            break;

        Gpio step_gpio(brush_entry.second, Gpio::Direction::OUT);
        brushes.push_back(Motor(std::move(step_gpio)));
    }
}

bool BrushController::paint(uint8_t brush_number, uint8_t steps, bool async)
{
    if (brushes.size() <= brush_number)
        return false;

    if (async) {
        brushes[brush_number].do_steps_async(steps);
    }
    else {
        brushes[brush_number].do_steps_blocking(steps);
        busy_wait_ms(paint_delay_ms);
    }

    return true;
}

void BrushController::wait_for_motors(bool do_paint_delay)
{
    for (auto &motor : brushes) {
        motor.wait_for_async();
    }

    if (do_paint_delay)
        busy_wait_ms(paint_delay_ms);
}
