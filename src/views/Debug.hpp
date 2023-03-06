#pragma once

#include "MessagePrinter.hpp"

namespace DisplayMessages
{
    class Debug
    {
    public:
    static message_list get(uint32_t x,
                              uint32_t y,
                              uint8_t r,
                            uint8_t g,
                            uint8_t b,
                            uint32_t pixels,
                            uint32_t all_pixels)
    {
        message_list messages;

        // RxxxGxxxBxxx xx%
        // XxxxxxYxxxxx

        std::string str;
        str = "R" + std::to_string(r);
        str += "G" + std::to_string(g);
        str += "B" + std::to_string(b);
        str += " " + std::to_string(100 * pixels / all_pixels) + "%";
        messages.push_back(std::move(str));

        str = "X" + std::to_string(x);
        str += "Y" + std::to_string(y);
        messages.push_back(std::move(str));

        return messages;
    }
};
}