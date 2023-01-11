#pragma once

#include <string>
#include <vector>
#include <optional>

class FileSelector {
public:
    using file_list_t = std::vector<std::string>;
    using file_list_iterator_t = file_list_t::iterator;
    
    FileSelector(const std::string &directory, const std::string &extension);
    ~FileSelector() = default;

    std::optional<std::string> enter_menu();
    
private:
    const std::string &directory;
    std::string extension;

    file_list_t file_list;

    bool load_file_list();
    std::string get_user_selection();
};