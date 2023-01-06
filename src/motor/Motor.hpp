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

    Motor(const Motor& other) = delete;

    void set_motor_speed(uint32_t steps_per_s);

    void do_steps_blocking(uint32_t steps);
    void do_steps_async(uint32_t steps);
    void wait_for_async(bool use_tight_loop = false);

    void set_direction(Direction new_direction);
    Direction get_direction() const;

private:
    Gpio direction_pin;
    Gpio step_pin;

    Direction direction = Direction::INC;
    uint32_t step_wait_us;

    semaphore_t sem;

    struct timer_payload {
        semaphore_t *sem;
        Gpio *step_pin;
        uint32_t steps_left;
    };

    repeating_timer_t timer;

    static bool repeating_timer_callback(repeating_timer_t *timer);
    static void send_pulse(Gpio &gpio);
};