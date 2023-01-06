#include "Button.hpp"

#include "hardware/gpio.h"
#include "pico/time.h"

#include "../config/Constants.hpp"

std::queue<uint8_t> Button::events;

Button::Button()
{
}

Button::~Button()
{
    events = {};
}

void Button::register_button(uint8_t gpio)
{
    gpio_init(gpio);
    gpio_pull_up(gpio);
    gpio_set_irq_enabled_with_callback(gpio, GPIO_IRQ_LEVEL_LOW | GPIO_IRQ_EDGE_FALL, true, handle_irq);
}

void Button::unregister_button(uint8_t gpio)
{
    button_callbacks.erase(gpio);
    gpio_deinit(gpio);
}

void Button::set_callback(uint8_t gpio, callback_t callback)
{
    button_callbacks[gpio] = callback;
}

void Button::remove_callback(uint8_t gpio)
{
    button_callbacks.erase(gpio);
}

bool Button::update_buttons()
{
    bool result = false;
    
    while (!events.empty()) {
        auto handler = button_callbacks.find(events.front());
        if (handler != button_callbacks.end())
            handler->second();
        events.pop();
        result = true;
    }

    return result;
}

// When button is in singleton move to class private
static bool pressed = false;
static uint8_t pressed_gpio = 0;
static alarm_id_t alarm_id;

void Button::handle_irq(uint gpio, uint32_t event)
{
    if (pressed_gpio != 0 && pressed_gpio != gpio) {
        // Ignore two buttons pressed at the same time
        return;
    }
    
    if (pressed) {
        cancel_alarm(alarm_id);
    }
    else {
        pressed = true;
        events.push(gpio);
    }

    alarm_id = add_alarm_in_ms(Constants::BUTTON_DEBOUNCE_MS, enable_button, nullptr, false);
}

int64_t Button::enable_button(alarm_id_t alarm_id, void *user_data)
{
    pressed = false;
    pressed_gpio = 0;

    return 0;
}

void Button::wait_for_button_event(bool use_tight_loop)
{
    while (!update_buttons()) {
        if (!use_tight_loop) {
            busy_wait_us(1);
        }
    }
}