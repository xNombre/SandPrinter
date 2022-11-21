#pragma once

#include <stdint.h>

#include <string>

#define SUPPORT_DISPLAY_SCROLL true

class Display {
    uint8_t sda_gpio, scl_gpio;
    uint8_t pos = 0, line = 0;
#if SUPPORT_DISPLAY_SCROLL
    std::string last_line;
#endif

public:
    Display(uint8_t sda_gpio, uint8_t scl_gpio);
    ~Display();

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
};