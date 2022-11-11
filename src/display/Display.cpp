#include "Display.hpp"

#include "display_hw.h"

Display::Display(unsigned sda_gpio, unsigned scl_gpio)
    : sda_gpio(sda_gpio), scl_gpio(scl_gpio)
{
    lcd_init(sda_gpio, scl_gpio);
}

Display::~Display()
{
    lcd_clear();
    lcd_deinit(sda_gpio, scl_gpio);
}

unsigned Display::get_cur_pos() const
{
    return pos;
}

unsigned Display::get_cur_line() const
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
void Display::print_scroll(const std::string &str)
{
    clear();
    print_line(last_line);
    print_line(str);
}
#endif

void Display::clear()
{
    pos = 0;
    line = 0;

    lcd_clear();
    lcd_home();
}