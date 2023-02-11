#include <stdio.h>
#include "pico/stdlib.h"
#include "debug/DebugMessage.hpp"
#include "config/Constants.hpp"
#include "display/Display.hpp"
#include "button/Button.hpp"
#include "gpio/Gpio.hpp"
#include "pico/time.h"
#include "motor/Motor.hpp"
#include "sd_card/Storage.hpp"
#include "bmp/Bmp.hpp"
#include "leds/StatusLed.hpp"
#include "config/DynamicConstants.hpp"
#include "printer/PrinterMenu.hpp"
#include "debug/ErrorHandler.hpp"

int main()
{
    stdio_init_all();

    print(MessageType::INFO, "SandPrinter Entry");
    
    auto led = StatusLed::get_instance();
    led->set_status(StatusLed::LedMode::ON);

    auto display = Display::get_instance();
    display->print_line("Sand Printer");
    display->print_line("Andrzej Perczak");

    sleep_ms(1000);
    led->set_status(StatusLed::LedMode::BLINK_FAST);
    sleep_ms(1000);

    auto storage = Storage::get_instance();
    auto status = storage->mount_sdcard();
    if (!status) {
        fatal_error(ErrorMessage::NO_SDCARD);
    }

    auto dynamic_config = DynamicConstants::get_instance();
    status = dynamic_config->load_constants();
    if (!status) {
        fatal_error("config.txt error");
    }

    led->set_status(StatusLed::LedMode::OFF);
    
    PrinterMenu main_menu;
    main_menu.enter_menu();

    panic("");

    return 0;
};