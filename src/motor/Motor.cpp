#include "Motor.hpp"

#include <utility>

Motor::Motor(Gpio &&direction_pin, Gpio &&step_pin)
    : direction_pin(std::move(direction_pin)),
    step_pin(std::move(step_pin))
{
    sem_init(&sem, 1, 1);
}

Motor::~Motor()
{
    wait_for_async();
}

void Motor::set_position_blocking(uint32_t new_position)
{
    sem_acquire_blocking(&sem);

    uint32_t delta;
    if (position > new_position) {
        delta = position - new_position;
    }
    else {
        delta = new_position + delta;
    }

    for (uint32_t i = 0; i < delta; i++) {
        step_pin.set_state(true);
        busy_wait_us(5000);
        step_pin.set_state(false);
    }

    sem_release(&sem);
}

void Motor::set_position_async(uint32_t new_position)
{
    sem_acquire_blocking(&sem);

    timer_payload *payload = new timer_payload;
    payload->sem = &sem;
    payload->cur_position = &position;
    payload->new_position = new_position;
    payload->increasing = new_position > position;
    payload->step_pin = &step_pin;

    add_repeating_timer_us(1000000, repeating_timer_callback, payload, &timer);
}

bool Motor::repeating_timer_callback(repeating_timer_t *timer)
{
    auto payload = (timer_payload *)timer->user_data;

    if (payload->increasing) {
        (*payload->cur_position)++;
    }
    else {
        (*payload->cur_position)--;
    }

    payload->step_pin->set_state(true);
    busy_wait_us(5000);
    payload->step_pin->set_state(false);
    
    if (*payload->cur_position == payload->new_position) {
        sem_release(payload->sem);
        return false;
    }

    return true;
}

void Motor::wait_for_async()
{
    while (sem_available(&sem) != 1) {
        busy_wait_us(1);
    }
}

uint32_t Motor::get_position() const
{
    return position;
}

void Motor::set_direction(Direction new_direction)
{
    if (direction == new_direction) {
        return;
    }

    sem_acquire_blocking(&sem);

    this->direction = direction;

    direction_pin.set_state(true);
    busy_wait_us(1000000);
    direction_pin.set_state(false);
    busy_wait_us(500000);
    
    sem_release(&sem);
}

auto Motor::get_direction() const -> Direction
{
    return direction;
}

