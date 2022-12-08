#pragma once

#include "../gpio/Gpio.hpp"
#include "pico/sem.h"
#include "pico/time.h"

class Motor {
public:
    enum class Direction {
        INC, DEC
    };
    
    Motor(Gpio &&direction_pin, Gpio &&step_pin);
    ~Motor();

    void set_motor_speed(uint32_t speed);

    void set_position_blocking(uint32_t new_position);
    void set_position_async(uint32_t new_position);
    void wait_for_async();
    uint32_t get_position() const;

    void set_direction(Direction new_direction);
    Direction get_direction() const;

private:
    Gpio direction_pin;
    Gpio step_pin;

    Direction direction = Direction::INC;
    uint32_t position = 0;
    uint32_t speed;

    semaphore_t sem;

    struct timer_payload {
        semaphore_t *sem;
        uint32_t *cur_position;
        uint32_t new_position;
        bool increasing;
        Gpio *step_pin;
    };

    repeating_timer_t timer;

    static bool repeating_timer_callback(repeating_timer_t *timer);
};