#pragma once

#include "MessagePrinter.hpp"

#include "../printer/FileSelector.hpp"

namespace DisplayMessages
{
    class FileMenu
    {
    public:
        static message_list get(const FileSelector::file_list_t& file_list,
                                const FileSelector::file_list_iterator_t &chosen_file)
        {
            message_list messages;

            // /Go back/
            // >file1
            // file2

            messages.push_back(">" + *chosen_file);
            messages.push_back(chosen_file + 1 == file_list.end() ? "" : *(chosen_file + 1));

            return messages;
        }
    };
}