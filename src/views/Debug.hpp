#pragma once

#include "MessagePrinter.hpp"

namespace DisplayMessages
{
    class Debug
    {
    public:
    static message_list print(uint32_t x,
                              uint32_t y,
                              uint8_t brush_idx,
                              uint8_t brush_val,
                              uint8_t r,
                              uint8_t g,
                              uint8_t b)
    {
        message_list messages;

        // RxxxGxxxBxxxVxxx
        // XxxxxxYxxxxx Brx

        std::string str;
        str = "R" + std::to_string(r);
        str += "G" + std::to_string(g);
        str += "B" + std::to_string(b);
        str += "V" + std::to_string(brush_val);
        messages.push_back(std::move(str));

        str = "X" + std::to_string(x);
        str += "Y" + std::to_string(y);
        str += " Br" + std::to_string(brush_idx);
        messages.push_back(std::move(str));

        return messages;
    }
};
}