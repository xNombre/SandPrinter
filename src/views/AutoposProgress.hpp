#pragma once

#include "MessagePrinter.hpp"

namespace DisplayMessages
{
    class AutoposProgress {
    public:
        static message_list get(bool x_axis)
        {
            message_list messages;

            // Autopositioning
            // Axis X/Y...

            messages.push_back("Autopositioning");

            std::string str;
            str = "Axis ";
            str += x_axis ? "X" : "Y";
            messages.push_back(std::move(str));

            return messages;
        }
    };
}