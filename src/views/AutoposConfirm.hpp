#pragma once

#include "MessagePrinter.hpp"

namespace DisplayMessages
{
    class AutoposConfirm {
    public:
        static message_list print()
        {
            message_list messages;

            // Autopos confirm
            // Press Ok

            messages.push_back("Autopos confirm");
            messages.push_back("Press Ok");
            
            return messages;
        }
    };
}