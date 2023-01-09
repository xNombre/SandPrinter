#pragma once

#include "MessagePrinter.hpp"

namespace DisplayMessages
{
    class PrintConfirm {
    public:
        static message_list get(std::string file_name,
                                  uint32_t pixels)
        {
            message_list messages;

            //file1
            //Pxxxxx Press Ok

            messages.push_back(file_name);

            std::string str;
            str = "P" + std::to_string(pixels);
            str += " Press Ok";
            messages.push_back(std::move(str));

            return messages;
        }
    };
}