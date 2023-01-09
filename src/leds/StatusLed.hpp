#pragma once

#include <memory>

#include <pico/time.h>

#include "../gpio/Gpio.hpp"

class StatusLed;
using StatusLedInstance = std::shared_ptr<StatusLed>;

class StatusLed {
public:
    enum class LedMode {
        OFF,
        ON,
        BLINK_SLOW,
        BLINK_FAST,
        BLINK_MANUAL
    };
    
    static StatusLedInstance get_instance();

    void set_status(LedMode mode);
    void blink(uint32_t timeout_ms = 100);

private:
    StatusLed();
    ~StatusLed();

    static bool timer_callback(repeating_timer_t *timer);
    
    static StatusLedInstance instance;

    Gpio led_gpio;
    LedMode mode;
    repeating_timer_t timer;
};