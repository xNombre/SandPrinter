#include <stdio.h>
#include "pico/stdlib.h"

#include "config/Constants.hpp"
#include "display/Display.hpp"
#include "button/Button.hpp"
#include "pico/time.h"

int main()
{
    stdio_init_all();

    Display disp(Constants::DISPLAY_SDA_GPIO, Constants::DISPLAY_SCL_GPIO);
    disp.print_line("Hai");

    int a = 0;
    Button btn;
    btn.register_button(Constants::BUTTON_UP_GPIO);
    btn.set_callback(Constants::BUTTON_UP_GPIO, [&] {
        disp.print_scroll("T " + std::to_string(++a));
                     });
    btn.register_button(Constants::BUTTON_DOWN_GPIO);
    btn.set_callback(Constants::BUTTON_DOWN_GPIO, [&] {
        disp.print_scroll("T " + std::to_string(--a));
                     });

    while (1) {
        sleep_ms(10);
        btn.update_buttons();
    }

    return 0;
};