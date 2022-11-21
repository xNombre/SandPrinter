#pragma once

#include <future>

#include "../gpio/Gpio.hpp"

class Motor {
public:
    enum class Direction {
        INC, DEC
    };
    
    Motor(Gpio &&direction_pin, Gpio &&step_pin);
    ~Motor() = default;

    void set_position_blocking(uint32_t position);
    std::future<void> set_position_async(uint32_t position);

private:
    Direction dir;
    uint32_t position = 0;
};