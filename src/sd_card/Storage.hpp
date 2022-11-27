#pragma once

#include <string>
#include <vector>
#include <optional>
#include <unordered_map>

#include "File.hpp"

#include "sd_card.h"

enum class FileMode {
    READ,
    WRITE,
    WRITE_APPEND
};

class Storage {
public:
    Storage();
    ~Storage();
    bool mount_sdcard();
    void unmount_sdcard();
    bool check_sdcard_available();

    bool file_exists(const std::string &file);
    std::vector<std::string> list_files_in_directory(const std::string &dirname = "");
    std::optional<File> open_file(const std::string &dirname, const std::string &filename, FileMode mode);
    
private:
    bool sdcard_mounted = false;
    sd_card_t *card;
    
    const std::unordered_map<FileMode, uint8_t> file_mode_map = {
        {FileMode::READ, FA_READ},
        {FileMode::WRITE, FA_WRITE},
        {FileMode::WRITE_APPEND, FA_OPEN_APPEND}
    };
};