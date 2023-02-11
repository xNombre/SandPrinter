#include "PrinterMenu.hpp"

#include "PrinterJob.hpp"
#include "PrinterAutopos.hpp"
#include "PrinterManualPos.hpp"
#include "FileSelector.hpp"

#include "../views/Views.hpp"
#include "../button/Button.hpp"
#include "../leds/StatusLed.hpp"
#include "../debug/ErrorHandler.hpp"

namespace Constant
{
    const std::string image_file_extension = "bmp";
    const std::string image_files_location = "images";
}

void PrinterMenu::enter_menu()
{
    auto status_led = StatusLed::get_instance();
    
    while (true) {
        auto option = get_option_for_user();

        switch (option) {
        case Entry::PRINT: {
            FileSelector file_sel(Constant::image_files_location, Constant::image_file_extension);
            PrinterJob printer_job;

            auto file_opt = file_sel.enter_menu();
            if (!file_opt)
                fatal_error("No file selected");

            auto ret = printer_job.prepare_job(file_opt.value());
            if (!ret)
                fatal_error("Image read failed!");

            status_led->set_status(StatusLed::LedMode::BLINK_SLOW);
            printer_job.start_job();
            status_led->set_status(StatusLed::LedMode::OFF);
            break;
        }
        case Entry::AUTOPOS: {
            PrinterAutopos autopos;
            autopos.enter_menu();
            break;
        }
        case Entry::MANUAL_POS: {
            PrinterManualPos manual_pos;
            manual_pos.enter_menu();
            break;
        }
        }
    }
}

auto PrinterMenu::get_option_for_user() -> Entry
{
    Entry current_option = Entry::PRINT;
    auto last_option = current_option;
    bool user_input_event_select = false;

    Button up(Constants::BUTTON_UP_GPIO);
    up.set_callback([&] {current_option--;});
    Button ok(Constants::BUTTON_OK_GPIO);
    ok.set_callback([&] {user_input_event_select = true;});
    Button down(Constants::BUTTON_DOWN_GPIO);
    down.set_callback([&] {current_option++;});

    while (!user_input_event_select) {
        auto message = DisplayMessages::MainMenu::get(current_option);
        MessagePrinter::print_message(message);

        last_option = current_option;
        while (last_option == current_option && !user_input_event_select)
            __wfi();

        StatusLed::get_instance()->blink();
    }

    return current_option;
}