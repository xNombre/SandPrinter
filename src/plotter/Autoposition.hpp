#pragma once

#include "../motor/Motor.hpp"

class Autoposition {
public:
    Autoposition(Motor& motor, Gpio& axis_switch, Direction direction = Direction::DEC);
    ~Autoposition() = default;

    bool do_autopositioning();

private:
    Motor &motor;
    Gpio &axis_gpio;
    Direction direction;
};