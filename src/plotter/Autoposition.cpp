#include "Autoposition.hpp"

#include "time.h"
#include "../config/DynamicConstants.hpp"

namespace Constants
{
    const uint32_t rough_steps_per_iteration = 3;
    const uint32_t precise_steps_per_iteration = 1;
    const uint32_t precise_wait_us = 10;
    const Gpio::PullResistor axis_switch_pull_mode = Gpio::PullResistor::UP;
}

Autoposition::Autoposition(Motor &motor, const uint8_t axis_switch_gpio)
    : motor(motor), axis_switch(axis_switch_gpio, Gpio::Direction::IN, Constants::axis_switch_pull_mode)
{
}

bool Autoposition::do_autopositioning()
{
    auto dynamic_config = DynamicConstants::get_instance();
    
    if(dynamic_config->value_is_available(DynamicConstants::Option::POSITIONING_ROUGH_SPEED) &&
       dynamic_config->value_is_available(DynamicConstants::Option::POSITIONING_PRECISE_SPEED)) {
        return false;
    }

    motor.set_motor_speed(dynamic_config->get_value_int(DynamicConstants::Option::POSITIONING_ROUGH_SPEED).value());
    do_switch_pingpong();

    motor.set_motor_speed(dynamic_config->get_value_int(DynamicConstants::Option::POSITIONING_PRECISE_SPEED).value());
    do_switch_pingpong();

    return true;
}

void Autoposition::do_switch_pingpong()
{
    motor.set_direction(Motor::Direction::DEC);
    
    while (!axis_switch.get_state()) {
        motor.do_steps_blocking(Constants::rough_steps_per_iteration);
    }

    motor.set_direction(Motor::Direction::INC);

    while (axis_switch.get_state()) {
        motor.do_steps_blocking(Constants::precise_steps_per_iteration);
        sleep_us(Constants::precise_wait_us);
    }
}
