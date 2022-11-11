#pragma once

#include <functional>
#include <unordered_map>
#include <queue>
#include "pico/stdlib.h"

class Button {
public:
    typedef std::function<void()> callback_t;
    
    Button();
    ~Button();

    Button(const Button &) = delete;
    Button &operator=(const Button &) = delete;

    void register_button(uint8_t gpio);
    void unregister_button(uint8_t gpio);
    
    void set_callback(uint8_t gpio, callback_t callback);
    void remove_callback(uint8_t gpio);

    // Has to be called periodically
    void update_buttons();

private:
    static std::queue<uint8_t> events;
    std::unordered_map<uint8_t, callback_t> button_callbacks;

    static void handle_irq(uint gpio, uint32_t event);
    static int64_t enable_button(alarm_id_t alarm_id, void *user_data);
};

