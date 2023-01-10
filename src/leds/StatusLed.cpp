#include "StatusLed.hpp"

#include "../config/Constants.hpp"

StatusLedInstance StatusLed::instance;

namespace Constant
{
    static uint32_t fast_blink_ms = 100;
    static uint32_t long_blink_ms = 500;
}

StatusLed::StatusLed()
    : led_gpio(Constants::STATUS_LED_GPIO, Gpio::Direction::OUT),
    mode(LedMode::OFF)
{
}

StatusLed::~StatusLed()
{
    cancel_repeating_timer(&timer);
}

StatusLedInstance StatusLed::get_instance()
{
    class public_cstor: public StatusLed {};

    if (!instance)
        instance = std::make_shared<public_cstor>();

    return instance;
}

void StatusLed::set_status(LedMode new_mode)
{
    if (mode == new_mode)
        return;

    mode = new_mode;

    cancel_repeating_timer(&timer);

    if (mode == LedMode::OFF || mode == LedMode::BLINK_MANUAL) {
        led_gpio.set_state(false);
        return;
    }

    led_gpio.set_state(true);
    
    if (mode == LedMode::ON) {
        return;
    }
    
    auto time = new_mode == LedMode::BLINK_FAST ?
        Constant::fast_blink_ms : Constant::long_blink_ms;


    bool ret = add_repeating_timer_ms(time, timer_callback, this, &timer);
    led_gpio.set_state(ret);
}

void StatusLed::blink(uint32_t timeout_ms)
{
    set_status(LedMode::BLINK_MANUAL);
    
    led_gpio.set_state(true);
    add_repeating_timer_ms(timeout_ms, timer_callback, this, &timer);
}

bool StatusLed::timer_callback(repeating_timer_t *timer)
{
    StatusLed *instance = (StatusLed *)timer->user_data;

    instance->led_gpio.set_state(!instance->led_gpio.get_state());

    return instance->mode != LedMode::BLINK_MANUAL;
}