#pragma once

#include "MessagePrinter.hpp"

namespace DisplayMessages
{
    class AutoposConfirm {
    public:
        static message_list print()
        {
            message_list messages;

            // Up/Down to move
            // Ok to return

            messages.push_back("Up/Down to move");
            messages.push_back("Ok to return");

            return messages;
        }
    };
}