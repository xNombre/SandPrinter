#include "Display.hpp"

#include "../config/Constants.hpp"

#include "display_hw.h"

DisplayInstance Display::instance;

Display::Display()
    : sda_gpio(Constants::DISPLAY_SDA_GPIO),
      scl_gpio(Constants::DISPLAY_SCL_GPIO)
{
    lcd_init(sda_gpio, scl_gpio);
}

Display::~Display()
{
    lcd_clear();
    lcd_deinit(sda_gpio, scl_gpio);
}

auto Display::get_instance() -> DisplayInstance
{
    class public_cstor: public Display {};
    
    if (!instance) {
        instance = std::make_shared<public_cstor>();
    }

    return instance;
}

uint8_t Display::get_cur_pos() const
{
    return pos;
}

uint8_t Display::get_cur_line() const
{
    return line;
}

void Display::print_line(const std::string &str)
{
    last_line = str;
    lcd_print(str.c_str());
    
    line = !line;
    pos = 0;

    lcd_setCursor(line, pos);
}

void Display::print(const std::string &str)
{
    last_line += str;
    lcd_print(str.c_str());
    pos += str.size();
}

#if SUPPORT_DISPLAY_SCROLL
void Display::print_scroll(const std::string &str, ScrollDirection dir)
{
    clear();
    if (dir == ScrollDirection::DOWN) {
        print_line(last_line);
        print_line(str);
    }
    else {
        print_line(str);
        print_line(last_line);
    }
}
#endif

void Display::clear()
{
    pos = 0;
    line = 0;

    lcd_clear();
    lcd_home();
}