#pragma once

#include "../gpio/Gpio.hpp"
#include "../motor/Motor.hpp"

class Autoposition {
public:
    Autoposition(Motor<>& motor, const uint8_t axis_switch_gpio);
    ~Autoposition() = default;

    bool do_autopositioning();

private:
    Motor<> &motor;
    Gpio axis_switch;

    void do_switch_pingpong();
};