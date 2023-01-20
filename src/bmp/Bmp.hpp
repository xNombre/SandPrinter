#pragma once

#include <vector>
#include <memory>
#include <optional>

#include "../sd_card/File.hpp"
#include "../color/ColorModels.hpp"

#include "bmp_structs.hpp"

class Bmp {
    static const size_t default_buf_size;

public:
    enum class ReadingOrder {
        ZIGZAG,
        FIRST_TO_LAST,
        LAST_TO_FIRST
    };
    struct pixel_position {
        uint32_t x, y;
    };

    Bmp(File &&file,
        ReadingOrder order = ReadingOrder::FIRST_TO_LAST,
        size_t buffer_size = default_buf_size);

    bool load_file();

    size_t get_width() const;
    size_t get_height() const;

    bool eof() const;
    rgb get_next_pixel();
    pixel_position get_current_pixel_position() const;

private:
    ReadingOrder order;

    size_t height;
    size_t width;
    size_t pixels; // height * width

    // BMP is 4 bytes aligned
    uint8_t padding_bytes;
    size_t bytes_per_width;

    size_t cur_width = 0;

    File &&file;

    size_t buffer_size;
    std::vector<uint8_t> buffer;
    size_t buffer_position = 0;
    size_t pixels_read = 0;

    bool refill_buffer();
    bmp_structures::pixel read_pixel_from_buffer();
    bmp_structures::pixel read_in_order(bool positive_order);
    void handle_width_alignment();
    bool check_bmp_header(const bmp_structures::bitmap_header &header);
    bool check_bmp_info(const bmp_structures::bitmap_info &info);
};