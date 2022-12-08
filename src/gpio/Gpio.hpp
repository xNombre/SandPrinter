#pragma once

#include <stdint.h>

class Gpio {
public:
    enum class Direction {
        IN,
        OUT
    };

    Gpio(uint8_t port, Direction dir);
    ~Gpio();
    
    void set_state(const bool value);
    bool get_state();

    bool get_direction() const;

private:
    uint8_t port;
    Direction dir;
};