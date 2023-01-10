#include "Storage.hpp"

#include "../config/Constants.hpp"
#include "storage_hw.h"

#include "rtc.h"

StorageInstance Storage::instance;

Storage::Storage()
    : card(sd_get_by_num(0))
{
    time_init();
}

Storage::~Storage()
{
    if (sdcard_mounted)
        unmount_sdcard();
}

std::shared_ptr<Storage> Storage::get_instance()
{
    class public_cstor: public Storage {};
    
    if (!instance) {
        instance = std::make_shared<public_cstor>();
    }

    return instance;
}

bool Storage::mount_sdcard()
{
    FRESULT fr = f_mount(&card->fatfs, card->pcName, 1);

    sdcard_mounted = FR_OK == fr;

    return sdcard_mounted;
}

void Storage::unmount_sdcard()
{
    f_unmount(card->pcName);
}

bool Storage::check_sdcard_available()
{
    auto result = f_getlabel(card->pcName, nullptr, nullptr);

    return result == FR_OK;
}

bool Storage::file_exists(const std::string &file)
{
    auto result = f_stat(file.c_str(), nullptr);
    
    return result == FR_OK;
}

std::vector<std::string> Storage::list_files_in_directory(const std::string &dirname)
{
    std::vector<std::string> files;
    DIR dir;
    FILINFO info;

    auto result = f_findfirst(&dir, &info, dirname.c_str(), "*\0");
    while (result == FR_OK && *info.fname) {
        files.push_back((char *)info.fname);
        result = f_findnext(&dir, &info);
    }
    f_closedir(&dir);

    return files;
}

std::optional<File> Storage::open_file(const std::string &dirname,
                                       const std::string &filename,
                                       File::Mode mode)
{
    FIL file;
    
    auto result = f_open(&file, filename.c_str(), file_mode_map.at(mode));
    if (result != FR_OK)
        return std::nullopt;

    return File(std::move(file));
}