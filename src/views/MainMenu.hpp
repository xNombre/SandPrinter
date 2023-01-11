#pragma once

#include <unordered_map>

#include "MessagePrinter.hpp"

#include "../printer/PrinterMenu.hpp"

namespace DisplayMessages
{
    namespace
    {
    class MainMenu {
        static const std::unordered_map<PrinterMenu::Entry, std::string> printer_menu_option_to_message;
        
    public:
        static message_list get(PrinterMenu::Entry menu_option)
        {
            message_list messages;
            const auto& option = printer_menu_option_to_message.at(menu_option);
            const auto &second_option = menu_option + 1 != PrinterMenu::Entry::DONOTUSE_LAST_ENTRY ?
                printer_menu_option_to_message.at(menu_option + 1) : "";

            //> Print
            //Manual position
            //Autoposition

            messages.push_back(">" + option);
            messages.push_back(second_option);

            return messages;
        }
    };


        const std::unordered_map<PrinterMenu::Entry, std::string> MainMenu::printer_menu_option_to_message = {
                {PrinterMenu::Entry::PRINT, "Print"},
                {PrinterMenu::Entry::MANUAL_POS, "Manual position"},
                {PrinterMenu::Entry::AUTOPOS, "Autoposition"}
        };
    }
}