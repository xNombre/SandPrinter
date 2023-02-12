#pragma once

#include <vector>
#include <memory>
#include <optional>

#include <sd_card/File.hpp>
#include <color/ColorModels.hpp>

#include "bmp_structs.hpp"
#include "Pixel.hpp"

class Bmp {
public:
    enum class ReadingOrder {
        ZIGZAG,
        FIRST_TO_LAST,
        LAST_TO_FIRST
    };

    Bmp(File &&file, ReadingOrder order);

    bool load_file();

    size_t get_width() const;
    size_t get_height() const;

    Pixel get_next_pixel();
    size_t get_current_x() const;
    size_t get_current_y() const;

    bool eof() const;

private:
    ReadingOrder order;
    File file;

    size_t height;
    size_t width;
    size_t pixels;

    uint8_t padding_bytes;
    size_t bytes_per_width;
    size_t bytes_per_width_with_padding;

    size_t cur_width;
    size_t pixels_read;

    size_t buffer_size;
    std::vector<uint8_t> buffer;
    size_t buffer_position;
    size_t remaining_size;

    bool current_reading_order;

    bool prepare_buffer_size();
    bool refill_buffer();

    bmp_structures::pixel read_pixel_from_buffer();
    bmp_structures::pixel read_next_pixel_in_order();

    bool check_bmp_header(const bmp_structures::bitmap_header &header);
    bool check_bmp_info(const bmp_structures::bitmap_info &info);
};