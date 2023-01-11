#pragma once

#include <memory>
#include <string>
#include <vector>
#include <optional>
#include <unordered_map>

#include "File.hpp"

#include "sd_card.h"

class Storage;
using StorageInstance = std::shared_ptr<Storage>;

class Storage {
public:
    static StorageInstance get_instance();

    bool mount_sdcard();
    void unmount_sdcard();
    bool check_sdcard_available();

    bool file_exists(const std::string &file);
    std::vector<std::string> list_files_in_directory(const std::string &dirname = "");
    std::optional<File> open_file(const std::string &filename, File::Mode mode);
    
private:
    Storage();
    ~Storage();

    static StorageInstance instance;

    bool sdcard_mounted = false;
    sd_card_t *card;
    
    const std::unordered_map<File::Mode, uint8_t> file_mode_map = {
        {File::Mode::READ, FA_READ},
        {File::Mode::WRITE, FA_WRITE},
        {File::Mode::WRITE_APPEND, FA_OPEN_APPEND}
    };
};