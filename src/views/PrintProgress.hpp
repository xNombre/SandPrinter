#pragma once

#include "MessagePrinter.hpp"
namespace DisplayMessages
{
    class PrintProgress {
        public:
        static message_list get(uint32_t pixels,
                                  uint32_t max_pixels,
                                  uint8_t percentage)
        {
            message_list messages;

            // Printing...
            // xxxxx/xxxxx xxx%

            messages.push_back("Printing...");

            std::string str;
            str = std::to_string(pixels);
            str += "/" + std::to_string(max_pixels);
            str += " " + std::to_string(percentage) + "%";
            messages.push_back(std::move(str));

            return messages;
        }
    };
}