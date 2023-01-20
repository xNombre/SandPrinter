#pragma once

#include <stdint.h>

class Gpio {
public:
    enum class Direction {
        IN,
        OUT
    };

    enum class PullResistor {
        NONE,
        UP,
        DOWN
    };

    Gpio(uint8_t port, Direction dir, PullResistor pull = PullResistor::NONE);
    ~Gpio();
    Gpio(const Gpio &other) = delete;
    Gpio &operator=(const Gpio &other) = delete;
    Gpio(Gpio &&other);

    void set_state(const bool value);
    bool get_state();

private:
    uint8_t port;
    Direction dir;
    bool state;
    bool gpio_moved = false;
};