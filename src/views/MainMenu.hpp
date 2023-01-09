#pragma once

#include <unordered_map>

#include "MessagePrinter.hpp"

#include "../printer/PrinterMenu.hpp"

namespace DisplayMessages
{
    class MainMenu {
        enum Option {
            PRINT = 0,
            MANUAL_POS,
            AUTOPOS
        };
        
        static const std::vector<std::string> options;
        static const std::unordered_map<PrinterMenu::Option, Option> printer_menu_option_to_messages;
        
    public:
        static message_list get(PrinterMenu::Option menu_option)
        {
            message_list messages;
            auto option = printer_menu_option_to_messages.at(menu_option);

            //> Print
            //Manual position
            //Autoposition

            messages.push_back(">" + options[option]);
            messages.push_back(options[option + 1]);

            return messages;
        }
    };

    const std::vector<std::string> MainMenu::options = {
            "Print",
            "Manual position",
            "Autoposition",
            ""
    };

    const std::unordered_map<PrinterMenu::Option, MainMenu::Option> MainMenu::printer_menu_option_to_messages = {
            {PrinterMenu::Option::PRINT, PRINT},
            {PrinterMenu::Option::MANUAL_POS, MANUAL_POS},
            {PrinterMenu::Option::AUTOPOS, AUTOPOS}
    };
}