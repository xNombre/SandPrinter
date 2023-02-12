#include "Button.hpp"

#include <hardware/gpio.h>
#include <hardware/irq.h>

#include <config/Constants.hpp>

std::map<uint8_t, Button *> Button::gpio_to_instance_map;

namespace Constant
{
    const uint32_t button_irq_event_mask = GPIO_IRQ_EDGE_FALL;
    const uint8_t button_debounce_ms = 150;
}

Button::Button(uint8_t gpio)
    : gpio(gpio),
    alarm_id(0)
{
    gpio_init(gpio);
    gpio_set_dir(gpio, false);
    gpio_pull_up(gpio);
    gpio_set_irq_enabled_with_callback(gpio, Constant::button_irq_event_mask, true, handle_irq);

    gpio_to_instance_map[gpio] = this;
}

Button::~Button()
{
    irq_set_enabled(IO_IRQ_BANK0, false);

    while (alarm_id != 0) {
        busy_wait_us(1);
    }

    gpio_to_instance_map.erase(gpio);
    gpio_set_irq_enabled(gpio, Constant::button_irq_event_mask, false);
    gpio_deinit(gpio);
    
    irq_set_enabled(IO_IRQ_BANK0, true);
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
    // gpio can get destroyed before irq is handled
    auto gpio_in_map = gpio_to_instance_map.find(gpio);
    if (gpio_in_map == gpio_to_instance_map.end())
        return;
    
    auto instance = gpio_in_map->second;

    if (instance->alarm_id != 0) {
        cancel_alarm(instance->alarm_id);
    }
    else {
        gpio_set_irq_enabled(gpio, Constant::button_irq_event_mask, false);
        if (instance->event_callback)
            instance->event_callback();
    }

    instance->alarm_id = add_alarm_in_ms(Constant::button_debounce_ms, enable_button, instance, false);
}

int64_t Button::enable_button(alarm_id_t alarm_id, void *user_data)
{
    auto instance = (Button *)user_data;

    if (!gpio_get(instance->gpio))
        return Constant::button_debounce_ms;

    instance->alarm_id = 0;
    gpio_set_irq_enabled(instance->gpio, Constant::button_irq_event_mask, true);

    return 0;
}