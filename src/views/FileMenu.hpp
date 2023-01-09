#pragma once

#include "MessagePrinter.hpp"

namespace DisplayMessages
{
    class FileMenu
    {
    public:
        static message_list get(std::string selected_file,
                                  std::string second_file)
        {
            message_list messages;

            // /Go back/
            // >file1
            // file2

            messages.push_back(">" + selected_file);
            messages.push_back(second_file);

            return messages;
        }
    };
}