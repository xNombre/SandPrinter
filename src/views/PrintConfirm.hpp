#pragma once

#include "MessagePrinter.hpp"

namespace DisplayMessages
{
    class PrintConfirm {
    public:
        static message_list get(std::string file_name,
                                  uint32_t width, uint32_t height)
        {
            message_list messages;

            //file1
            //Xxxxx Yxxxx

            messages.push_back(file_name);

            std::string str;
            str = "X" + std::to_string(width);
            str += " Y" + std::to_string(height);
            messages.push_back(std::move(str));

            return messages;
        }
    };
}