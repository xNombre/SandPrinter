#include "Motor.hpp"

#include <utility>

namespace Constants
{
    const uint8_t set_pin_delay_us = 5;
    const uint32_t us_in_s = 1'000'000;
    const uint8_t default_motor_speed = 1;
    const uint32_t max_steps_per_s = us_in_s / set_pin_delay_us * 2;
}

Motor::Motor(Gpio &&direction_pin, Gpio &&step_pin)
    : direction_pin(std::move(direction_pin)),
    step_pin(std::move(step_pin))
{
    sem_init(&sem, 1, 1);
    set_motor_speed(Constants::default_motor_speed);
}

Motor::~Motor()
{
    wait_for_async(true);
}

void Motor::set_motor_speed(uint32_t steps_per_s)
{
    if (steps_per_s > Constants::max_steps_per_s)
        steps_per_s = Constants::max_steps_per_s;
        
    step_wait_us = Constants::us_in_s / steps_per_s;
}

void Motor::do_steps_blocking(uint32_t steps)
{
    if (steps == 0)
        return;
    
    sem_acquire_blocking(&sem);

    for (; steps > 0; steps--) {
        send_pulse(step_pin);
        busy_wait_us(step_wait_us);
    }

    sem_release(&sem);
}

void Motor::do_steps_async(uint32_t steps)
{
    if (steps == 0)
        return;
    
    sem_acquire_blocking(&sem);

    timer_payload *payload = new timer_payload;
    payload->sem = &sem;
    payload->steps_left = steps;
    payload->step_pin = &step_pin;

    add_repeating_timer_us(step_wait_us, repeating_timer_callback, payload, &timer);
}

bool Motor::repeating_timer_callback(repeating_timer_t *timer)
{
    auto payload = (timer_payload *)timer->user_data;

    payload->steps_left--;
    send_pulse(*payload->step_pin);

    if (payload->steps_left == 0) {
        sem_release(payload->sem);
        delete payload;
        return false;
    }

    return true;
}

void Motor::wait_for_async(bool use_tight_loop)
{
    while (sem_available(&sem) != 1) {
        if (!use_tight_loop) {
            busy_wait_us(1);
        }
    }
}

void Motor::set_direction(Direction new_direction)
{
    if (direction == new_direction) {
        return;
    }

    sem_acquire_blocking(&sem);

    direction = new_direction;
    direction_pin.set_state(direction == Direction::DEC);

    sem_release(&sem);
}

auto Motor::get_direction() const -> Direction
{
    return direction;
}

void Motor::send_pulse(Gpio &gpio)
{
    gpio.set_state(true);
    busy_wait_us(Constants::set_pin_delay_us);
    gpio.set_state(false);
    busy_wait_us(Constants::set_pin_delay_us);
}