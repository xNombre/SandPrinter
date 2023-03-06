#include "BrushController.hpp"

#include <pico/time.h>

#include <gpio/Gpio.hpp>
#include <debug/DebugMessage.hpp>

BrushController::BrushController()
{
    auto dynamic_config = DynamicConstants::get_instance();

    paint_delay_ms = dynamic_config->get_value_int(DynamicConstants::Option::PAINT_DELAY).value();
    auto motor_speed = dynamic_config->get_value_int(DynamicConstants::Option::BRUSH_MOTOR_SPEED).value();
    
    for (const auto &brush_entry : brush_list) {
        if (!dynamic_config->value_is_available(brush_entry.first))
            break;

        Gpio step_gpio(brush_entry.second, Gpio::Direction::OUT);
        FakeGpio fake_dir_gpio;
        Motor motor(std::move(fake_dir_gpio), std::move(step_gpio));
        motor.set_motor_speed(motor_speed);
        brushes.push_back(std::move(motor));
    }
}

bool BrushController::paint(uint8_t brush_number, uint8_t steps, bool async)
{
    if (brushes.size() <= brush_number)
        return false;

    if (steps > 0) {
        print(MessageType::LOG, "Brush number: " + std::to_string(brush_number) + ", do steps: " + std::to_string(steps));
    }

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
