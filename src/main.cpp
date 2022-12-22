#include <stdio.h>
#include "pico/stdlib.h"

#include "config/Constants.hpp"
#include "display/Display.hpp"
#include "button/Button.hpp"
#include "gpio/Gpio.hpp"
#include "pico/time.h"
#include "motor/Motor.hpp"
#include "sd_card/Storage.hpp"
#include "bmp/Bmp.hpp"

int main()
{
    stdio_init_all();
    Storage stor;

    Gpio mobo_led(25, Gpio::Direction::OUT);
    mobo_led.set_state(true);

    Gpio yl_led(Constants::MOTOR_BRUSH4_GPIO, Gpio::Direction::OUT);
    
    Display disp(Constants::DISPLAY_SDA_GPIO, Constants::DISPLAY_SCL_GPIO);
    disp.print_line("Hai");

    //stor.mount_sdcard();
    if (!stor.mount_sdcard())
    {
        disp.print_scroll("Insert sd");
        while (!stor.mount_sdcard()) {
            sleep_ms(500);
        }
    }
    disp.print_scroll("SD detected");
    //sleep_ms(1500);

    /*if (stor.file_exists("file"))
        disp.print_scroll("Jest plik");


    auto vec = stor.list_files_in_directory("images");
    for (auto s : vec) {
        disp.print_scroll(s);
        sleep_ms(500);
    }*/

    /*auto bmp = stor.open_file("", "test.bmp", FileMode::READ);
    Bmp bitmap(std::move(*bmp), ReadingOrder::ZIGZAG);

    if (bitmap.load_file()) {
        disp.print_scroll("BMP OK");
    }
    else {
        disp.print_scroll("BMP NOK");
    }

    sleep_ms(1500);
    int a = 0;
    while (!bitmap.eof()) {
        auto pix = bitmap.get_next_pixel();
        std::string eo = std::to_string(a++) + ". " + std::to_string(pix.red) + " " +
            std::to_string(pix.green) + " " + std::to_string(pix.blue);
        disp.print_scroll(eo);
        sleep_ms(1200);
    }*/

    /*int a = 0;
    Button btn;
    btn.register_button(Constants::BUTTON_UP_GPIO);
    btn.set_callback(Constants::BUTTON_UP_GPIO, [&] {
        disp.print_scroll("T " + std::to_string(++a));
        yl_led.set_state(a % 2);
                     });
    btn.register_button(Constants::BUTTON_DOWN_GPIO);
    btn.set_callback(Constants::BUTTON_DOWN_GPIO, [&] {
        disp.print_scroll("T " + std::to_string(--a));
        yl_led.set_state(a % 2);
                     });
    
    while (1) {
        sleep_ms(10);
        btn.update_buttons();
    }*/

    Gpio dir(Constants::MOTOR_DIR_X_GPIO, Gpio::Direction::OUT);
    Gpio step(Constants::MOTOR_STEP_X_GPIO, Gpio::Direction::OUT);
    Motor mot(std::move(dir), std::move(step));

    Gpio dir2(Constants::MOTOR_DIR_Y_GPIO, Gpio::Direction::OUT);
    Gpio step2(Constants::MOTOR_STEP_Y_GPIO, Gpio::Direction::OUT);
    Motor mot2(std::move(dir2), std::move(step2));

    mot.set_direction(Motor::Direction::INC);
    mot.set_position_async(5);
    mot2.set_position_async(7);
    mot.set_direction(Motor::Direction::DEC);
    mot.set_position_async(2);
    mot.wait_for_async();
    mot2.wait_for_async();
    
    while (1);

    return 0;
};