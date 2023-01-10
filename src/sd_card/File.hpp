#pragma once

#include <vector>
#include <memory>
#include <string>

#include "ff.h"

class File {
public:
    enum class Mode {
        READ,
        WRITE,
        WRITE_APPEND
    };
    
    File(FIL &&file);
    ~File();

    // Buffer stands for the maximum lenght of a line to be read
    std::string read_line(const uint32_t buffer = 256);
    std::vector<uint8_t> read(const uint32_t size);

    bool write(const std::string &msg);
    bool write(const std::vector<uint8_t> &data);

    bool seek(const uint32_t offset);
    uint32_t tell();
    uint32_t get_size();
    bool eof();
    bool flush();

private:
    FIL file;
};