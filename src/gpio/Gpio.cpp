#include "Gpio.hpp"

#include "hardware/gpio.h"

Gpio::Gpio(uint8_t port, Direction dir, PullResistor pull)
    : port(port), dir(dir), state(false)
{
    gpio_init(port);
    gpio_set_dir(port, dir == Direction::IN ? false : true);

    if (dir == Direction::IN) {
        if (pull == PullResistor::UP) {
            gpio_pull_up(port);
        }
        else if (pull == PullResistor::DOWN) {
            gpio_pull_down(port);
        }
    }
}

Gpio::~Gpio()
{
    gpio_deinit(port);
}

void Gpio::set_state(const bool value)
{
    if (dir != Direction::OUT)
        return;

    state = value;
    gpio_put(port, value);
}

bool Gpio::get_state()
{
    if (dir != Direction::IN)
        return state;
    
    return gpio_get(port);
}
