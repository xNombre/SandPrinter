#include "Gpio.hpp"

#include "hardware/gpio.h"

Gpio::Gpio(uint8_t port, Direction dir)
    : port(port), dir(dir)
{
    gpio_init(port);
    gpio_set_dir(port, dir == Direction::IN ? false : true);
}

Gpio::~Gpio()
{
    gpio_deinit(port);
}

void Gpio::set_state(const bool value)
{
    if (dir == Direction::OUT)
        gpio_put(port, value);
}

bool Gpio::get_state()
{
    if (dir == Direction::IN)
        return gpio_get(port);
    return false;
}
