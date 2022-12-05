#include "File.hpp"

File::File(FIL &&file)
    : file(std::move(file))
{

}

File::~File()
{
    flush();
    f_close(&file);
}

uint32_t File::get_size()
{
    return f_size(&file);
}

std::string File::read_line(const uint32_t buffer)
{
    char *read_buffer = new char[buffer];

    auto result = f_gets(read_buffer, buffer, &file);
    if (result != read_buffer) {
        delete[] read_buffer;
        return std::string();
    }

    std::string line = read_buffer;
    delete[] read_buffer;

    return line;
}

std::vector<uint8_t> File::read(const uint32_t size)
{
    std::vector<uint8_t> arr(size);
    UINT read_bytes;

    auto result = f_read(&file, arr.data(), size, &read_bytes);
    
    if (result != FR_OK) {
        return {};
    }
    if (read_bytes != size) {
        arr.resize(read_bytes);
    }

    return arr;
}

bool File::write(const std::string &msg)
{
    return f_printf(&file, msg.c_str()) > -1;
}

bool File::write(const std::vector<uint8_t> &data)
{
    UINT bytes_written;
    
    auto result = f_write(&file, data.data(), data.size(), &bytes_written);

    return result == FR_OK && bytes_written == data.size();
}

bool File::seek(const uint32_t offset)
{
    return f_lseek(&file, offset) == FR_OK;
}

uint32_t File::tell()
{
    return f_tell(&file);
}

bool File::eof()
{
    return f_eof(&file);
}

bool File::flush()
{
    return f_sync(&file) == FR_OK;
}