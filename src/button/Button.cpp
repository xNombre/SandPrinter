#include "Button.hpp"

#include "hardware/gpio.h"

#include "../config/Constants.hpp"

std::map<uint8_t, Button *> Button::gpio_to_instance_map;

Button::Button(uint8_t gpio)
    : gpio(gpio),
    alarm_id(0)
{
    gpio_init(gpio);
    gpio_pull_up(gpio);
    gpio_set_irq_enabled_with_callback(gpio, GPIO_IRQ_LEVEL_LOW | GPIO_IRQ_EDGE_FALL, true, handle_irq);

    gpio_to_instance_map[gpio] = this;
}

Button::~Button()
{
    gpio_to_instance_map.erase(gpio);
    gpio_deinit(gpio);
}

void Button::set_callback(callback_t callback)
{
    event_callback = callback;
}

void Button::remove_callback()
{
    event_callback = nullptr;
}

void Button::handle_irq(uint gpio, uint32_t event)
{
    auto instance = gpio_to_instance_map[gpio];

    if (instance->alarm_id != 0) {
        cancel_alarm(instance->alarm_id);
    }
    else if (instance->event_callback) {
        instance->event_callback();
    }

    instance->alarm_id = add_alarm_in_ms(Constants::BUTTON_DEBOUNCE_MS, enable_button, instance, false);
}

int64_t Button::enable_button(alarm_id_t alarm_id, void *user_data)
{
    auto instance = (Button *)user_data;

    instance->alarm_id = 0;

    return 0;
}