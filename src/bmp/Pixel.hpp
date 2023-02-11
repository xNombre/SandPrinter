#pragma once

#include <color/ColorModels.hpp>

struct Pixel {
    rgb color;
    uint32_t x, y;

    Pixel(rgb color = rgb(), uint32_t x = 0, uint32_t y = 0)
        : color(color), x(x), y(y)
    { }
};