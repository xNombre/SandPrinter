#pragma once

#include "MessagePrinter.hpp"

namespace DisplayMessages
{
    class MainMenu {
        static const std::vector<std::string> options;
        
    public:
        enum Option {
            PRINT = 0,
            MANUAL_POS,
            AUTO_POS
        };

        static message_list print(Option option)
        {
            message_list messages;

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
}