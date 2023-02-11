#pragma once

#include <stdint.h>

#include <color/ColorModels.hpp>

using hword = uint8_t;
using word = uint16_t;
using dword = uint32_t;
using qword = uint64_t;

class bmp_structures {
public:
    struct bitmap_header
    {
        word signature;
        dword file_size;
        word bfReserved1;
        word bfReserved2;
        dword offset_to_array;
    } __packed;

    struct bitmap_info {
        dword header_size;
        dword image_width;
        dword image_height;
        word planes;
        word bits_per_pixel;
        dword compression;
        dword image_size;
    } __packed;

    struct pixel {
        hword blue;
        hword green;
        hword red;

        rgb get_rgb()
        {
            return rgb(red, green, blue);
        }
    } __packed;
};