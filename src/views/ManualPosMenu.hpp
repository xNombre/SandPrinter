#pragma once

#include "MessagePrinter.hpp"

namespace DisplayMessages
{
    class ManualPosMenu {
        static const std::vector<std::string> options;

    public:
        enum Option {
            X = 0,
            Y
        };

        static message_list get(Option option)
        {
            message_list messages;

            //> X
            //  Y

            messages.push_back("> " + options[option]);
            messages.push_back("  " + options[option + 1]);

            return messages;
        }
    };
    
    const std::vector<std::string> ManualPosMenu::options = {
        "X",
        "Y",
        ""
    };
}