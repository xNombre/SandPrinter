#pragma once

#include <string>

#define SUPPORT_DISPLAY_SCROLL true

class Display {
    unsigned sda_gpio, scl_gpio;
    unsigned pos = 0, line = 0;
#if SUPPORT_DISPLAY_SCROLL
    std::string last_line;
#endif

public:
    Display(unsigned sda_gpio, unsigned scl_gpio);
    ~Display();

    unsigned get_cur_pos() const;
    unsigned get_cur_line() const;

    void print(const std::string &str);
    void print_line(const std::string &str);
#if SUPPORT_DISPLAY_SCROLL
    void print_scroll(const std::string &str);
#endif
    
    void clear();
};