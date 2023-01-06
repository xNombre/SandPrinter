#pragma once

#include <string>
#include <vector>

#include "../display/Display.hpp"

namespace DisplayMessages
{
typedef std::vector<std::string> message_list;

class MessagePrinter {
public:
    static void print_message(Display &disp, message_list messages)
    {
        for (const auto &msg : messages) {
            disp.print_line(msg);
        }
    }
};
}