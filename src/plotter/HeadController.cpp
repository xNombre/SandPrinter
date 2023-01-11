#include "HeadController.hpp"

#include <utility>

#include "../config/Constants.hpp"
#include "Autoposition.hpp"

HeadController::HeadController()
    : x_axis_motor(Gpio(Constants::MOTOR_DIR_X_GPIO, Gpio::Direction::OUT),
                         Gpio(Constants::MOTOR_STEP_X_GPIO, Gpio::Direction::OUT)),
      y_axis_motor(Gpio(Constants::MOTOR_DIR_Y_GPIO, Gpio::Direction::OUT),
                       Gpio(Constants::MOTOR_STEP_Y_GPIO, Gpio::Direction::OUT))
{
    auto dynamic_config = DynamicConstants::get_instance();

    max_x = dynamic_config->get_value_int(DynamicConstants::Option::MAX_WIDTH).value();
    max_y = dynamic_config->get_value_int(DynamicConstants::Option::MAX_HEIGHT).value();

    duty_speed = dynamic_config->get_value_int(DynamicConstants::Option::DUTY_MOVE_SPEED).value();
    free_speed = dynamic_config->get_value_int(DynamicConstants::Option::FREE_MOVE_SPEED).value();

    set_mode(MotorMode::DUTY);
}

bool HeadController::autoposition_axes()
{
    return autoposition_axis(x_axis_motor, Constants::LIMIT_SWITCH_X_GPIO) &&
           autoposition_axis(y_axis_motor, Constants::LIMIT_SWITCH_Y_GPIO);
}

bool HeadController::autoposition_axis(Motor &axis_motor, const uint8_t axis_switch_gpio)
{
    Autoposition autopos(axis_motor, axis_switch_gpio);

    return autopos.do_autopositioning();
}

bool HeadController::goto_position(uint32_t new_x, uint32_t new_y, bool async)
{
    if (max_y < new_y || max_x < new_x) {
        return false;
    }

    int64_t steps = (int64_t)new_x - (int64_t)x_pos;
    auto dir = Motor::Direction::INC;
    if (steps < 0) {
        steps = std::abs(steps);
        dir = Motor::Direction::DEC;
    }
    move_motor(x_axis_motor, dir, steps, async);
    x_pos = new_x;

    steps = (int64_t)new_y - (int64_t)y_pos;
    dir = Motor::Direction::INC;
    if (steps < 0) {
        steps = std::abs(steps);
        dir = Motor::Direction::DEC;
    }
    move_motor(y_axis_motor, dir, steps, async);
    y_pos = new_y;

    return true;
}

void HeadController::move_motor_raw(Axis axis, Motor::Direction dir, uint32_t steps, bool async)
{
    auto &motor = axis == Axis::X ? x_axis_motor : y_axis_motor;
    move_motor(motor, dir, steps, async);
}

void HeadController::move_motor(Motor &motor, Motor::Direction dir, uint32_t steps, bool async)
{
    if (steps == 0) {
        return;
    }

    motor.set_direction(dir);

    if (async)
        motor.do_steps_async(steps);
    else
        motor.do_steps_blocking(steps);
}

void HeadController::wait_for_motors()
{
    x_axis_motor.wait_for_async();
    y_axis_motor.wait_for_async();
}

uint32_t HeadController::get_x() const
{
    return x_pos;
}

uint32_t HeadController::get_y() const
{
    return y_pos;
}

void HeadController::set_mode(MotorMode mode)
{
    const auto &speed = mode == MotorMode::DUTY ? duty_speed : free_speed;

    x_axis_motor.set_motor_speed(speed);
    y_axis_motor.set_motor_speed(speed);
}