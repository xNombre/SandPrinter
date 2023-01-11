#pragma once

#include "Gpio.hpp"

class FakeGpio {
public:
    FakeGpio(uint8_t port, Gpio::Direction dir, Gpio::PullResistor pull = Gpio::PullResistor::NONE) { }
    FakeGpio() {}
    
    void set_state(const bool value) { }
    bool get_state() { return false; }
};