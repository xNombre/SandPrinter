#include "Bmp.hpp"

#include <string.h>
#include "../debug/ErrorHandler.hpp"
#include "../debug/DebugMessage.hpp"
namespace Constant
{
    const dword bmp_signature = 0x4D42;
    const word bmp_planes = 1;
    const word bmp_rgb_in_pixel = 24;
    const dword bmp_no_compression = 0;
    const size_t max_buffer_size = 200 * 1024; // 200KB
}

const size_t Bmp::default_buf_size = 16 * 1024; // 16KB

Bmp::Bmp(File &&file, ReadingOrder order, size_t buffer_size)
    : file(std::move(file)),
      order(order),
     buffer_size(buffer_size)
{ }

bool Bmp::check_bmp_header(const bmp_structures::bitmap_header &header)
{
    if (header.signature != Constant::bmp_signature) {
        return false;
    }

    return true;
}

bool Bmp::check_bmp_info(const bmp_structures::bitmap_info &info)
{
     if (info.planes != Constant::bmp_planes) {
        return false;
     }
     if (info.bits_per_pixel != Constant::bmp_rgb_in_pixel) {
         return false;
     }
     if (info.compression != Constant::bmp_no_compression) {
         return false;
     }
     
     return true;
}

bool Bmp::load_file()
{
    bmp_structures::bitmap_header header;
    bmp_structures::bitmap_info info;

    auto data = file.read(sizeof(header));
    if (data.empty())
        return false;
    
    memcpy(&header, data.data(), sizeof(header));
    if (!check_bmp_header(header))
        return false;

    data = file.read(sizeof(info));
    if (data.empty())
        return false;

    memcpy(&info, data.data(), sizeof(info));
    if (!check_bmp_info(info))
        return false;

    height = info.image_height;
    width = info.image_width;
    pixels = height * width;
    remaining_size = info.image_size;

    bytes_per_width = width * sizeof(bmp_structures::pixel);
    
    // BMP is padded to 4 bytes, extract required padding
    // Substract 4 bytes from actual size to get remainder
    // Select last two bits via AND
    padding_bytes = (0b100 - bytes_per_width) & 0b11;
    bytes_per_width += padding_bytes;

    // To handle different pixel ordering buffer has to
    // be at least a size of image width
    if (bytes_per_width > buffer_size) {
        buffer_size = bytes_per_width;
    }
    
    if (buffer_size > Constant::max_buffer_size) {
        print(MessageType::WARN, "Image width too large! " + std::to_string(buffer_size));
        return false;
    }

    // buffer size should be a multiple of width_bytes
    // to be able to handle zigzag ordering
    buffer_size -= buffer_size % bytes_per_width;

    if (!file.seek(header.offset_to_array)) {
        return false;
    }

    return refill_buffer();
}

size_t Bmp::get_width() const
{
    return width;
}

size_t Bmp::get_height() const
{
    return height;
}

bool Bmp::eof() const
{
    return pixels == pixels_read;
}

Pixel Bmp::get_next_pixel()
{
    if (pixels_read >= pixels) {
        // eof, return empty
        return Pixel();
    }

    pixels_read++;

    bool positive_order = false;
    if (order == ReadingOrder::ZIGZAG) {
        positive_order = (pixels_read - 1) / width % 2 == 0;
    }
    else if (order == ReadingOrder::FIRST_TO_LAST) {
        positive_order = true;
    }

    auto color = read_in_order(positive_order).get_rgb();
    auto position = get_current_pixel_position();

    return Pixel(color, position.x, position.y);
}

bmp_structures::pixel Bmp::read_in_order(bool positive_order)
{
    bmp_structures::pixel pixel;
    
    if (buffer_position >= buffer.size()) {
        refill_buffer();
    }

    auto pixel_index = buffer_position;
    if (!positive_order) {
        pixel_index += bytes_per_width - padding_bytes -
            sizeof(bmp_structures::pixel) - 2 * (buffer_position % bytes_per_width);
    }

    memcpy(&pixel, &buffer[pixel_index], sizeof(bmp_structures::pixel));

    buffer_position += sizeof(bmp_structures::pixel);
    cur_width++;

    if (cur_width == width) {
        buffer_position += padding_bytes;
        cur_width = 0;
    }

    return pixel;
}

bool Bmp::refill_buffer()
{
    buffer.clear();

    auto bytes_to_read = std::min(buffer_size, remaining_size);
    remaining_size -= bytes_to_read;

    print(MessageType::INFO, "Refill buffer, read: " + std::to_string(bytes_to_read) + "bytes, remaining_size: " + std::to_string(remaining_size));
    auto data = file.read(bytes_to_read);

    if (data.empty() || data.size() != bytes_to_read) {
        fatal_error(ErrorMessage::BUFFER_REFILL_ERROR);
    }

    buffer_position = 0;
    buffer = std::move(data);

    return true;
}

auto Bmp::get_current_pixel_position() const -> pixel_position
{
    pixel_position pos;
    auto y_pos = (pixels_read - 1) / width;
    auto cur_width = (pixels_read - 1) % width;
    
    pos.x = y_pos % 2 == 0 ? cur_width : width - 1 - cur_width;
    pos.y = y_pos;

    return pos;
}