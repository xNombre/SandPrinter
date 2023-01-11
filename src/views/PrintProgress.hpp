#pragma once

#include "MessagePrinter.hpp"
namespace DisplayMessages
{
    class PrintProgress {
        public:
        static message_list get(uint32_t pixels,
                                  uint32_t all_pixels)
        {
            message_list messages;

            // Printing...
            // xxxxx/xxxxx xxx%

            messages.push_back("Printing...");

            std::string str;
            str = std::to_string(pixels);
            str += "/" + std::to_string(all_pixels);
            str += " " + std::to_string(pixels / all_pixels) + "%";
            messages.push_back(std::move(str));

            return messages;
        }
    };
}