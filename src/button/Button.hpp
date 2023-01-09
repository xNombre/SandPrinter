#pragma once

#include <functional>
//#include <memory>
#include <map>
//#include <queue>

#include "pico/stdlib.h"
#include "pico/time.h"

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

    // Has to be called periodically
    // Return true if any button event has been registered
    //bool update_buttons();

    // Carefull, blocks until event is registered
    //void wait_for_button_event(bool use_tight_loop = false);

private:
    //std::shared_ptr<Button> instance;

    //static std::queue<uint8_t> events;
    //std::unordered_map<uint8_t, callback_t> button_callbacks;

    uint8_t gpio;
    callback_t event_callback;
    alarm_id_t alarm_id;

    static std::map<uint8_t, Button *> gpio_to_instance_map;

    static void handle_irq(uint gpio, uint32_t event);
    static int64_t enable_button(alarm_id_t alarm_id, void *user_data);
};

