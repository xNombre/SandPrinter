#pragma once

#include <future>

#include "../gpio/Gpio.hpp"

class Brush {
public:
    Brush(Gpio &&step_pin);
    ~Brush() = default;

    void paint(uint32_t steps);
    std::future<void> paint_blocking(uint32_t steps);

private:
    Gpio step_pin;
};