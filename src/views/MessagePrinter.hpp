#pragma once

#include <string>
#include <vector>

#include "../display/Display.hpp"

namespace DisplayMessages
{
    typedef std::vector<std::string> message_list;
}

class MessagePrinter {
public:
    static void print_message(DisplayMessages::message_list messages)
    {
        auto display = Display::get_instance();
        display->clear();
        
        for (const auto &msg : messages) {
            display->print_line(msg);
        }
    }
};
