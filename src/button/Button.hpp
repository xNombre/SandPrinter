#pragma once

#include <functional>
#include <map>

#include <pico/stdlib.h>
#include <pico/time.h>

class Button {
public:
    enum class TriggerMode {
        SHORT_CLICK,
        LONG_PRESS,
        PRESS_AND_HOLD
    };

    typedef std::function<void()> callback_t;

    Button(uint8_t gpio);
    ~Button();

    void set_callback(callback_t callback);
    void remove_callback();

private:
    uint8_t gpio;
    callback_t event_callback;
    alarm_id_t alarm_id;

    static std::map<uint8_t, Button *> gpio_to_instance_map;

    static void handle_irq(uint gpio, uint32_t event);
    static int64_t enable_button(alarm_id_t alarm_id, void *user_data);
};

