#pragma once

#include <stdint.h>

#include <memory>
#include <string>

#define SUPPORT_DISPLAY_SCROLL true

class Display;
using DisplayInstance = std::shared_ptr<Display>;

class Display {
public:
    static DisplayInstance get_instance();
    
    uint8_t get_cur_pos() const;
    uint8_t get_cur_line() const;

    void print(const std::string &str);
    void print_line(const std::string &str);
#if SUPPORT_DISPLAY_SCROLL
    enum class ScrollDirection {
        UP, DOWN
    };
    void print_scroll(const std::string &str, ScrollDirection dir = ScrollDirection::DOWN);
#endif
    
    void clear();

private:
    Display();
    ~Display();

    static DisplayInstance instance;

    uint8_t sda_gpio, scl_gpio;
    uint8_t pos = 0, line = 0;
#if SUPPORT_DISPLAY_SCROLL
    std::string last_line;
#endif
};